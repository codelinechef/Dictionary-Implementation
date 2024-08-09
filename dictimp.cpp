#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <ctime>
#include <cstdlib>

using namespace std;

const int ALPHABET_SIZE = 26; // Number of characters in the English alphabet

// Trie Node structure
struct TrieNode
{
    TrieNode *children[ALPHABET_SIZE];
    bool isEndOfWord;

    TrieNode()
    {
        isEndOfWord = false;
        for (int i = 0; i < ALPHABET_SIZE; ++i)
        {
            children[i] = nullptr;
        }
    }
};
class Trie
{
private:
    TrieNode *root;
    vector<string> recentSearches;
    string wordOfTheDay;

    // Helper method to convert a character to an index (0-25)
    int charToIndex(char ch)
    {
        return ch - 'a';
    }

    // Helper method to collect words starting from the given node
    void collectWords(TrieNode *node, string prefix, vector<string> &words)
    {
        if (node->isEndOfWord)
        {
            words.push_back(prefix);
        }
        for (int i = 0; i < ALPHABET_SIZE; ++i)
        {
            if (node->children[i])
            {
                collectWords(node->children[i], prefix + char(i + 'a'), words);
            }
        }
    }

public:
    Trie()
    {
        root = new TrieNode();
        // Initialize Word of the Day
        wordOfTheDay = "example";
        srand(time(0)); // Seed for random number generation
    }

    // Method to insert a word into the Trie
    void insert(const string &word)
    {
        TrieNode *node = root;
        for (char ch : word)
        {
            int index = charToIndex(ch);
            if (!node->children[index])
            {
                node->children[index] = new TrieNode();
            }
            node = node->children[index];
        }
        node->isEndOfWord = true;
    }

    // Method to search for a word in the Trie
    bool search(const string &word)
    {
        TrieNode *node = root;
        for (char ch : word)
        {
            int index = charToIndex(ch);
            if (!node->children[index])
            {
                return false;
            }
            node = node->children[index];
        }
        return node->isEndOfWord;
    }

    // Method to get the Word of the Day
    string getWordOfTheDay()
    {
        return wordOfTheDay;
    }

    // Method to update the Word of the Day
    void updateWordOfTheDay()
    {
        // Sample words
        vector<string> words = {"example", "trie", "dictionary", "hangman", "search"};
        wordOfTheDay = words[rand() % words.size()];
    }

    // Method to add a recent search
    void addRecentSearch(const string &word)
    {
        if (recentSearches.size() >= 5)
        {
            recentSearches.erase(recentSearches.begin());
        }
        recentSearches.push_back(word);
    }

    // Method to display recent searches
    void displayRecentSearches()
    {
        if (recentSearches.empty())
        {
            cout << "No recent searches." << endl;
            return;
        }
        cout << "Recent Searches:" << endl;
        for (const string &word : recentSearches)
        {
            cout << "- " << word << endl;
        }
    }

    // Method to play Hangman
    void playHangman()
    {
        string word = "hangman"; // Example word for Hangman
        string guessedWord(word.size(), '_');
        vector<char> guessedLetters;
        int attempts = 6; // Number of attempts allowed
        char guess;

        while (attempts > 0 && guessedWord != word)
        {
            cout << "Word: " << guessedWord << endl;
            cout << "Attempts remaining: " << attempts << endl;
            cout << "Guessed letters: ";
            for (char c : guessedLetters)
            {
                cout << c << ' ';
            }
            cout << endl;
            cout << "Enter a letter: ";
            cin >> guess;
            guess = tolower(guess);
            guessedLetters.push_back(guess);

            bool correctGuess = false;
            for (size_t i = 0; i < word.size(); ++i)
            {
                if (word[i] == guess)
                {
                    guessedWord[i] = guess;
                    correctGuess = true;
                }
            }

            if (!correctGuess)
            {
                --attempts;
            }
        }

        if (guessedWord == word)
        {
            cout << "Congratulations! You've guessed the word: " << word << endl;
        }
        else
        {
            cout << "Game Over! The word was: " << word << endl;
        }
    }
};
int main()
{
    Trie trie;
    int choice;
    string word;

    while (true)
    {
        cout << "Menu:" << endl;
        cout << "1. Insert a word" << endl;
        cout << "2. Search for a word" << endl;
        cout << "3. Show Word of the Day" << endl;
        cout << "4. Update Word of the Day" << endl;
        cout << "5. Show Recent Searches" << endl;
        cout << "6. Play Hangman" << endl;
        cout << "7. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "Enter word to insert: ";
            cin >> word;
            trie.insert(word);
            trie.addRecentSearch(word);
            break;
        case 2:
            cout << "Enter word to search: ";
            cin >> word;
            if (trie.search(word))
            {
                cout << "Word found in the dictionary." << endl;
            }
            else
            {
                cout << "Word not found in the dictionary." << endl;
            }
            trie.addRecentSearch(word);
            break;
        case 3:
            cout << "Word of the Day: " << trie.getWordOfTheDay() << endl;
            break;
        case 4:
            trie.updateWordOfTheDay();
            cout << "Word of the Day updated." << endl;
            break;
        case 5:
            trie.displayRecentSearches();
            break;
        case 6:
            trie.playHangman();
            break;
        case 7:
            cout << "Exiting program." << endl;
            return 0;
        default:
            cout << "Invalid choice. Please try again." << endl;
            break;
        }
    }
}
