#include <iostream>
#include <string>
using namespace std;

struct Song {
    string title;
    Song* next;
};

// Insert a song at the start
Song* insertAtStart(Song* head, const string& songTitle) {
    Song* newSong = new Song();
    newSong->title = songTitle;

    if (head == NULL) {
        newSong->next = newSong;
        return newSong;
    }

    Song* temp = head;
    while (temp->next != head) {
        temp = temp->next;
    }

    newSong->next = head;
    temp->next = newSong;
    head = newSong;

    return head;
}

// Insert a song at the end
Song* insertAtEnd(Song* head, const string& songTitle) {
    Song* newSong = new Song();
    newSong->title = songTitle;

    if (head == NULL) {
        newSong->next = newSong;
        return newSong;
    }

    Song* temp = head;
    while (temp->next != head) {
        temp = temp->next;
    }

    temp->next = newSong;
    newSong->next = head;

    return head;
}

// Display playlist
void displayPlaylist(Song* head) {
    if (head == NULL) {
        cout << "Playlist is empty.\n";
        return;
    }

    Song* temp = head;
    cout << "\n?? Playlist:\n";
    do {
        cout << "?? " << temp->title << endl;
        temp = temp->next;
    } while (temp != head);
}

// Free memory
void deletePlaylist(Song* head) {
    if (head == NULL)
        return;

    Song* current = head->next;
    while (current != head) {
        Song* next = current->next;
        delete current;
        current = next;
    }
    delete head;
}

int main() {
    Song* playlist = NULL;
    int choice;
    string title;

    do {
        cout << "\n?? Playlist Menu:\n";
        cout << "1. Insert song at start\n";
        cout << "2. Insert song at end\n";
        cout << "3. Display playlist\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter song title (one word only): ";
                cin >> title;
                playlist = insertAtStart(playlist, title);
                break;
            case 2:
                cout << "Enter song title (one word only): ";
                cin >> title;
                playlist = insertAtEnd(playlist, title);
                break;
            case 3:
                displayPlaylist(playlist);
                break;
            case 0:
                deletePlaylist(playlist);
                cout << "Exiting and memory freed.\n";
                break;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 0);

    return 0;
}

