import os
import time
from google.oauth2 import service_account
from googleapiclient.discovery import build
import vlc  # For audio playback

# Google Drive API credentials (Service Account)
SERVICE_ACCOUNT_FILE = 'path_to_service_account_credentials.json'  # Replace with your service account credentials file
SCOPES = ['https://www.googleapis.com/auth/drive']

# ID of the folder containing song files in Google Drive
FOLDER_ID = 'your_folder_id_here'  # Replace with your folder ID

# Function to authenticate and retrieve song files from Google Drive
def fetch_song_files():
    try:
        creds = service_account.Credentials.from_service_account_file(SERVICE_ACCOUNT_FILE, scopes=SCOPES)
        service = build('drive', 'v3', credentials=creds)

        song_files = []
        page_token = None

        while True:
            response = service.files().list(q=f"'{FOLDER_ID}' in parents",
                                            fields='nextPageToken, files(name, webViewLink)').execute()
            files = response.get('files', [])
            for file in files:
                song_files.append({
                    'name': file['name'],
                    'webLink': file['webViewLink']
                })

            page_token = response.get('nextPageToken', None)
            if page_token is None:
                break

        return song_files
    except Exception as e:
        print(f"An error occurred while fetching song files: {e}")
        return []

# Function to download a song file from Google Drive
def download_song_file(song):
    try:
        os.system(f"wget -O '{song['name']}' '{song['webLink']}'")
    except Exception as e:
        print(f"An error occurred while downloading the song '{song['name']}': {e}")

# Function to play songs using VLC media player
def play_song(song):
    try:
        instance = vlc.Instance('--input-repeat=-1', '--fullscreen')  # VLC instance with repeat and fullscreen
        player = instance.media_player_new()
        media = instance.media_new(song)
        media.get_mrl()
        player.set_media(media)
        player.play()
        time.sleep(5)  # Play each song for 5 seconds (adjust as needed)
        player.stop()
    except Exception as e:
        print(f"An error occurred while playing the song '{song}': {e}")

# Fetch song files from Google Drive and download them
song_files = fetch_song_files()
for song in song_files:
    download_song_file(song)

# Function to display the music player dashboard menu
def display_dashboard():
    print("===============================")
    print("       Music Player Menu       ")
    print("===============================")
    print("1. Play all songs")
    print("2. Exit")
    print("===============================")

# Function to handle user choice
def handle_choice(choice):
    if choice == '1':
        print("========== Autoplaying Music ==========")
        if song_files:
            print("Welcome to the Music Player!")
            print(f"Found {len(song_files)} songs in your Google Drive folder.")
            print("Enjoy the music!\n")

            for idx, song in enumerate(song_files, start=1):
                print(f"Now playing: {song['name']} ({idx}/{len(song_files)})")
                play_song(song['name'])
                if idx < len(song_files):
                    input("Press Enter to play the next song...")
            
            print("\nAll songs have been played. Hope you enjoyed the music!")
        else:
            print("No songs found in the Google Drive folder.")
    elif choice == '2':
        print("Exiting the Music Player...")
        # Add any necessary cleanup code or exit statements here
        pass
    else:
        print("Invalid choice. Please enter a valid option.")

# Display the dashboard and handle user choice
while True:
    display_dashboard()
    user_choice = input("Enter your choice (1-2): ")
    handle_choice(user_choice)
    if user_choice == '2':
        break
