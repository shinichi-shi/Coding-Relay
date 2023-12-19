#include <iostream>
#include <vector>
#include <string>

// Song structure with title, artist, and description
struct Song {
    std::string title;
    std::string artist;
    std::string description;
};

// Function to display the music player dashboard menu
void displayMenu() {
    std::cout << "===== Music Player Dashboard =====" << std::endl;
    std::cout << "1. Play a song" << std::endl;
    std::cout << "2. Display playlist" << std::endl;
    std::cout << "3. Exit" << std::endl;
    std::cout << "=================================" << std::endl;
    std::cout << "Enter your choice: ";
}

// Function to clear the console screen
void clearScreen() {
    std::cout << "\033[2J\033[1;1H"; // ANSI escape codes to clear screen
}

int main() {
    // Create a vector to store songs
    std::vector<Song> playlist;

    // Add 10 sample songs with titles, artists, and descriptions
    Song song1 = {"Song Title 1", "Artist 1", "Description for Song 1"};
    Song song2 = {"Song Title 2", "Artist 2", "Description for Song 2"};
    Song song3 = {"Song Title 3", "Artist 3", "Description for Song 3"};
    Song song4 = {"Song Title 4", "Artist 4", "Description for Song 4"};
    Song song5 = {"Song Title 5", "Artist 5", "Description for Song 5"};
    Song song6 = {"Song Title 6", "Artist 6", "Description for Song 6"};
    Song song7 = {"Song Title 7", "Artist 7", "Description for Song 7"};
    Song song8 = {"Song Title 8", "Artist 8", "Description for Song 8"};
    Song song9 = {"Song Title 9", "Artist 9", "Description for Song 9"};
    Song song10 = {"Song Title 10", "Artist 10", "Description for Song 10"};

    // Add songs to the playlist
    playlist.push_back(song1);
    playlist.push_back(song2);
    playlist.push_back(song3);
    playlist.push_back(song4);
    playlist.push_back(song5);
    playlist.push_back(song6);
    playlist.push_back(song7);
    playlist.push_back(song8);
    playlist.push_back(song9);
    playlist.push_back(song10);

    int choice;
    do {
        clearScreen(); // Clear the screen
        displayMenu(); // Display dashboard menu
        std::cin >> choice;

        switch(choice) {
            case 1: {
                clearScreen();
                std::cout << "=== Play a Song ===" << std::endl;
                std::cout << "Select a song to play:" << std::endl;
                for (size_t i = 0; i < playlist.size(); ++i) {
                    std::cout << i + 1 << ". " << playlist[i].title << " - " << playlist[i].artist << std::endl;
                }
                std::cout << "Enter song number: ";
                int songNumber;
                std::cin >> songNumber;
                if (songNumber >= 1 && songNumber <= static_cast<int>(playlist.size())) {
                    clearScreen();
                    std::cout << "Now playing: " << playlist[songNumber - 1].title << " - " << playlist[songNumber - 1].artist << std::endl;
                    std::cout << "Description: " << playlist[songNumber - 1].description << std::endl;
                } else {
                    std::cout << "Invalid song number." << std::endl;
                }
                std::cout << "Press Enter to continue...";
                std::cin.ignore();
                std::cin.get();
                break;
            }
            case 2: {
                clearScreen();
                std::cout << "=== Playlist ===" << std::endl;
                for (size_t i = 0; i < playlist.size(); ++i) {
                    std::cout << "Song " << i + 1 << ": " << playlist[i].title << " - " << playlist[i].artist << std::endl;
                    std::cout << "Description: " << playlist[i].description << std::endl;
                    std::cout << std::endl;
                }
                std::cout << "Press Enter to continue...";
                std::cin.ignore();
                std::cin.get();
                break;
            }
            case 3:
                clearScreen();
                std::cout << "Exiting the music player..." << std::endl;
                break;
            default:
                clearScreen();
                std::cout << "Invalid choice. Please enter a valid option." << std::endl;
                std::cout << "Press Enter to continue...";
                std::cin.ignore();
                std::cin.get();
        }
    } while (choice != 3);

    return 0;
}
