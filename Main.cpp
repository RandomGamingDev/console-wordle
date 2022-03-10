#include<iostream>
#include<fstream>
#include<array>
#include<vector>
#include<map>
#include<string>
#include<stdlib.h>
#include<time.h>

const unsigned int length = 5, chances = 5;

enum LetterIs {
	Match,
	Contained,
	Nonexistent
};
std::map<LetterIs, std::string> displayLetterIs{
	{ Match, "Match" },
	{ Contained, "Contained" },
	{ Nonexistent, "Nonexistent" }
};

std::vector<std::string> ExtractText(std::string filePath) {
	std::ifstream file; file.open(filePath);
	std::vector<std::string> text;
	if (file.is_open()) {
		while (!file.eof()) {
			std::string line;
			getline(file, line);
			text.push_back(line);

		}
		file.close();
	}
	else {
		std::cout << "We weren't able to open the file";
		std::cin.get();
	}
	return text;
}

int main() {
	srand((unsigned)time(NULL));
	std::vector<std::string> text = ExtractText("words.txt");
	while (true) {
		std::string wordle = text[rand() % text.size() + 1];
		for (int i = 0; i < chances; i++) {
			std::cout << "Guess [" << i + 1 << '/' << chances << "]: ";
			std::string guess; std::cin >> guess;
			if (guess.length() == length) {
				std::array<LetterIs, length> lettersAre;
				for (int j = 0; j < length; j++) {
					if (guess[j] == wordle[j]) lettersAre[j] = Match;
					else {
						bool nonexistent = true;
						for (int k = 0; k < length; k++) if (guess[j] == wordle[k]) {
							lettersAre[j] = Contained;
							nonexistent = false;
						}
						if (nonexistent) {
							lettersAre[j] = Nonexistent;
						}
					}
				}
				bool won = true;
				for (int j = 0; j < length; j++) {
					std::cout << '#' << j + 1 << "\n  " << guess[j] << ": " << displayLetterIs[lettersAre[j]] << '\n';
					if (lettersAre[j] != Match) won = false;
				}
				if (won) {
					std::cout << "You won!\n";
					break;
				}
			}
			else {
				std::cout << "That was invalid, please try again\n";
				i--;
			}
		}
		std::cout << "The wordle is: " << wordle << '\n';
	}
	return 0;
}