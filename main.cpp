#include<iostream>
#include<cstdlib>
#include<ctime>
#include<fstream>

int main() {
	
	using namespace std;
	

	// seeds the random number generator only once
	srand(static_cast<unsigned int>(time(0)));
	char PlayAgain;


	//best score and data saves;
	int bestScore;
	ifstream inFile("highscore.txt");
	if (inFile>>bestScore)
	{
		cout<<"Current high score: "<<bestScore<<" guesses.\n";
	}
	else
	{
		bestScore = 999;//default score if file doesnt exist
	}
	inFile.close();

	


	do {
		int secretNumber = rand() % 100 + 1; //this will generate a random number from 1-100
		int max_Guesses = 7;
		int guess_Count = 0;
		int guess = 0; // Initialize to 0 or another non-secret value
		cout << "I'm thinking of a number between 1 and 100. You have " << max_Guesses << " guesses." << endl;

		do {
			//calculates the remaining guesses and displays it
			int guesses_Remaining = max_Guesses - guess_Count;

			// Display the number of the current guess (guess_Count + 1) and guesses left.
			cout << "\nGuess #" << guess_Count + 1;
			cout << " (" << guesses_Remaining << " " << "guesses" << " " << "left)" << endl;


			cout << "Enter your guess(1-100): ";
			cin >> guess;

			if (cin.fail())//checks if the input is valid
			{
				cin.clear(); // clears error flag
				cin.ignore(32767, '\n');//discards the bad input from user
				cout << "Invalid input! That counts as a guess." << endl;
				guess_Count = guess_Count + 1; //punishes for bad input to make it harder
				continue;
			}

			// checks if the number entered is between 1 and 100
			if (guess < 1 || guess > 100) {
				cout << "Guess must be between 1 and 100! That counts as a guess." << endl;
				guess_Count = guess_Count + 1;
				continue;
			}

			guess_Count = guess_Count + 1; 

			// --- Too High / Too Low Logic ---
			if (guess != secretNumber)
			{
				{
					if (guess > secretNumber) {
						cout << "Too high!" << endl;
					}
					else
					{
						cout << "Too low!" << endl;
					}
				}
			}

		} while (guess != secretNumber && guess_Count < max_Guesses);


		// --- Final Win/Lose Message ---
		if (guess == secretNumber) {
			cout << "\nCongratulations! You guessed right in " <<" " << guess_Count<<" " << "guesses!" << endl;
		}
		if (guess_Count<bestScore)
		{
			cout << "New high score!!!\n";
			bestScore = guess_Count;


			ofstream outFile("highscore.txt");
			outFile << bestScore;
			outFile.close();
		}
		else
		{
			cout << "Your best score remains" <<" " << bestScore <<" " << "guesses.\n";
		}
		if (guess != secretNumber)
		{
			cout << "\nYou lose! You ran out of guesses :(" << endl;
			cout << "The secret number was " << " " << secretNumber << endl;
		}

		// --- Ask to Play Again ---
		do
		{
			cout << "\nWould you like to play again? (y/n): ";
			cin >> PlayAgain;
		} while (PlayAgain != 'y' && PlayAgain != 'Y' && PlayAgain != 'n' && PlayAgain != 'N');

		
	} while (PlayAgain == 'y' || PlayAgain == 'Y');

	cout << "\nThanks for playing! Goodbye." << endl;
	return 0;
}