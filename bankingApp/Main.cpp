//#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <sstream>
#include <typeinfo>
#include <string.h>
#include "Current.h"
#include "Savings.h"
#include "Transaction.h"

/// <summary>
///	Sets the active account
/// </summary>
/// <param name="viewAccount">		account being viewed		</param>
/// <param name="openAcc">		vector of open accounts		</param>
/// <returns>		Value that is the index of the account that is being viewed		</returns>
int viewingAccount(int viewAccount, std::vector<Account *> openAcc)
{
    int VA;
    // if a viewAccount hasnt been set
    // then set it as last account made
    if (viewAccount == -1)
    {
        VA = (openAcc.size() - 1);
    }
    else
    {
        VA = viewAccount;
    }
    return VA;
}

/// <summary>
/// Function to create tokens from input sting and output them into a vector
/// </summary>
/// <param name="inp">		The input string		</param>
/// <returns>		parameters - used in user interface		</returns>
std::vector<std::string> createTokens(std::string inp)
{
    std::vector<std::string> parameters;

    char *cstr = new char[inp.length() + 1];
    strcpy(cstr, inp.c_str()); // copies string to array

    char *token;
    token = strtok(cstr, " "); // splits into token seperated by spaces

    while (token != NULL)
    {
        // Pushes the tokens onto the parameter vector
        parameters.push_back(token);
        token = strtok(NULL, " "); // splits into token seperated by spaces
    }

    return parameters;
}

// Needs to be transaction so the both objects are swapped

/// <summary>
/// swaps a transaction for sorting means
/// </summary>
void swap(Transaction *xp, Transaction *yp)
{
    Transaction temp = *xp;
    *xp = *yp;
    *yp = temp;
}

// Bubble sort could be good as best case is when list is already sorted
/// <summary>
/// A bubble sort algorithm
/// </summary>
/// <param name="history">		vector of transactions to be sorted		</param>
void bubbleSort(std::vector<Transaction> &history) // pass by ref
{
    int i;
    int x;
    // This loop is to increace effieicentcy of bubbble sort
    for (i = 0; i < history.size() - 1; i++)
    {
        // only need to loop through half the list as the last half is already in order
        for (x = 0; x < history.size() - i - 1; x++)
        {
            // swap value if left is bigger than right
            if (history[x].getValue() > history[x + 1].getValue())
                // pass by reference to properly swap them
                swap(&history[x], &history[x + 1]);
        }
    }
}

// Quick sort chosen in end
// Chosen to keep history in main unaltered which means the benifits of bubble sort would be minimal

/// <summary>
/// Quick sort algorithm
/// </summary>
/// <param name="history">		vector of transactions to be sorted		</param>
/// <param name="low">		leftmost index		</param>
/// <param name="high">		rightmost index		</param>
void quickSort(std::vector<Transaction> &history, int low, int high) // pass by ref
{
    // end condition
    if (low < high)
    {
        int pivot = high;
        ;
        int i = low - 1;

        // loops through vector and puts all cases lower than pivot on left and all cases above on right
        for (int j = low; j <= high - 1; j++)
        {
            if (history[j].getValue() <= history[pivot].getValue())
            {
                i += 1;
                swap(&history[i], &history[j]);
            }
        }
        swap(&history[i + 1], &history[high]);

        int PI = i + 1;
        // recursive funstion that does the same for everything but the partition index
        // the partition index is sorted so only the indexes below and above this index need to be sorted (+-1)
        quickSort(history, low, PI - 1);
        quickSort(history, PI + 1, high);
    }
}

void binarySearch(double searchValue, std::vector<Transaction> history)
{
    // for (int i = 0; i < history.size(); i++) { std::cout << history[i].toString() << std::endl; }
    bool found = false;
    int start = 0;
    int end = (history.size() - 1);
    int pivot = (end + start) / 2;
    while (found == false)
    {
        // exit conditions
        if (history[pivot].getValue() == searchValue)
        {
            found = true;
            std::cout << "Found: " << history[pivot].toString() << std::endl;
        }
        else if (start >= end)
        {
            found = true;
            std::cout << "Value not found" << std::endl;
        }
        // starts searching lower half of vector left
        else if (history[pivot].getValue() > searchValue)
        {
            end = pivot - 1;
            pivot = ((end + start) / 2);
        }
        // starts searching higher half of vector left
        else if (history[pivot].getValue() < searchValue)
        {
            start = pivot + 1;
            pivot = ((end + start) / 2);
        }
        else
        {
            found = true;
            std::cout << "Value not found" << std::endl;
        }
    }
}

/// <summary>
/// Combines together the sort and search algorithms
/// </summary>
/// <param name="searchValue">		value to be searched for		</param>
/// <param name="history">		vector of transactions to be searched		</param>
void search(int searchValue, std::vector<Transaction> history)
{
    quickSort(history, 0, (history.size() - 1));
    // for (int i = 0; i < history.size(); i++) { std::cout << history[i].toString() << std::endl; }
    binarySearch(searchValue, history);

    // searchTokens[3].erase(searchTokens[3].begin());
    // for (int i = 0; i < searchTokens.size(); i++) { std::cout << searchTokens[i] << std::endl; }

    // Could use createTokens to create tokens of the toString function
    // Allows us to find the value
    // This would mean there is no need for a getAmount() in Transaction

    /* Using tokens to do job of getValue()
std::vector <std::string>  searchTokens = createTokens(history[t].toString());

        // if statement gets the searchAmount to equal the correct token
        if (searchTokens[1] == "initial")
        {
            searchTokens[3].erase(searchTokens[3].begin());
            //std::cout << std::stod(searchTokens[3]) << std::endl;
            searchAmount = std::stod(searchTokens[3]);
        }
        else
        {
            searchTokens[2].erase(searchTokens[2].begin());
            //std::cout << std::stod(searchTokens[2]) << std::endl;
            searchAmount = std::stod(searchTokens[2]);
        }
*/
}

int main()
{
    std::vector<std::string> parameters;
    std::string userCommand;
    // you may also want to store a collection of opened accounts here
    // Needs to be a list of pointers as absract classes cannot be initiated
    std::vector<Account *> openAccounts;
    // viewAccount specsifies the account that is being viewed
    // -1 represtents no account ahs been selected
    int viewAccount = -1;
    /*
    Savings s(true);
    openAccounts.push_back(&s);
    */
    /* // Prefer way below personally
 Account* a = new Savings(true);
 openAccounts.push_back(a);
 */

    // std::cout << openAccounts[0]->toString();

    // Below is the user interface
    std::cout << "~~~ Welcome to LincBank! ~~~" << std::endl;
    std::cout << "open type initial_deposit: open a current (1), savings (2) or ISA (3) account\nview[index]: view balance and recent transactions\nwithdraw sum: withdraw funds from most recently viewed account\ndeposit sum: deposit funds into most recently viewed account\ntransfer src dest sum: transfer funds between accounts\nproject years: project balance forward in time\nexit: close this application\noptions: view these options again\nsearch value: searches for value in most reacently viewed account\n\n"
              << std::endl;

    // exit condition
    while (userCommand != "exit")
    {
        parameters.clear(); // clear ready for next command
        std::string command;
        bool empty = false;
        std::cout << std::endl
                  << ">>> ";

        std::getline(std::cin, userCommand);

        parameters = createTokens(userCommand); // Creates vector of commands

        // for (int i = 0; i < parameters.size(); i++) { std::cout << parameters[i] << "END"; } // Used to test what given code does
        // Splits into tokens that can be used to define user input

        // Define all commands as per the brief
        // Condition to stop an input of empty commands
        if (parameters.size() == 0)
        {
            empty = true;
        }
        else
        {
            command = parameters[0];
        }

        // Makes sure an input is put in
        // If the parameters are empty the statements will be skipped
        if (empty == true)
        {
            std::cout << "Enter an input";
        }
        // exit
        else if (command.compare("exit") == 0)
        {
            std::cout << "Exiting program" << std::endl;
        }
        // Makes sure the input isnt to big
        else if (parameters.size() > 4)
        {
            std::cout << "ERROR: Too many commands have been entered" << std::endl;
        }

        else if (command.compare("options") == 0)
        {
            std::cout << "open type initial_deposit: open a current (1), savings (2) or ISA (3) account\nview[index]: view balance and recent transactions\nwithdraw sum: withdraw funds from most recently viewed account\ndeposit sum: deposit funds into most recently viewed account\ntransfer src dest sum: transfer funds between accounts\nproject years: project balance forward in time\nexit: close this application\noptions: view these options again\nsearch value: searches for value in most reacently viewed account\n\n"
                      << std::endl;
        }

        else if (command.compare("open") == 0)
        {
            // allow a user to open an account
            // e.g., Account* a = new Savings(...);
            // This statement is used to make sure that the user has entered a proper command
            // If the user enter a command without a type (e.g. open ) then an error is thrown
            // Happens because parameter[1] is called but dosent exist
            if (parameters.size() == 1)
            {
                std::cout << "ERROR : Need to enter an account type" << std::endl;
            } // Makes sure there are not too many commands
            else if (parameters.size() > 3)
            {
                std::cout << "ERROR: Too many inputs" << std::endl;
            }
            else if (parameters[1] == "1")
            {
                // Current account
                try
                {
                    bool currUnique = true; // Ensures only one current account is made
                    for (int s = 0; s < openAccounts.size(); s++)
                    {
                        if (openAccounts[s]->toString()[0] == 'C')
                        {
                            std::cout << "Only one current account can be created" << std::endl;
                            currUnique = false;
                        }
                    }
                    // This statement is used to make sure that the user has entered a proper command
                    // If the user enter a command without a an amount (e.g. open 1 ) then an error is thrown
                    // Happens because parameter[2] is called but dosent exist
                    if (parameters.size() == 2)
                    {
                        std::cout << "Enter an initial deposit" << std::endl;
                    } // Condition that only one curernt account exists and that initial deposit is >= 0
                    else if (currUnique == true && std::stod(parameters[2]) >= 0)
                    {
                        // Creates account and adds it to account vector
                        Account *a = new Current(std::stod(parameters[2]));
                        openAccounts.push_back(a);
                        viewAccount = -1;
                        std::cout << "Current account created" << std::endl;
                        std::cout << a->toString() << std::endl;
                    }
                    else if (currUnique == true)
                    {
                        std::cout << "Current initial balance must be >= \x9C 0" << std::endl;
                    }
                    else
                    {
                        throw 505;
                    }
                } // catch statement for any other errors
                catch (...)
                {
                    std::cout << "Enter a valid input" << std::endl;
                }
            }
            else if (parameters[1] == "2")
            {
                // Savings account
                // Can have multiple savings accounts
                try
                {
                    if (parameters.size() == 2)
                    {
                        std::cout << "Enter an initial deposit" << std::endl;
                    } // Initial deposit >= 0
                    else if (std::stod(parameters[2]) >= 0)
                    {
                        Account *a = new Savings(false, std::stod(parameters[2]));
                        openAccounts.push_back(a);
                        viewAccount = -1;
                        std::cout << "Savings account created" << std::endl;
                        std::cout << a->toString() << std::endl;
                    }
                    else if (std::stod(parameters[2]) < 0)
                    {
                        std::cout << "Savings initial balance must be >= \x9C 0" << std::endl;
                    }
                    else
                    {
                        throw 505;
                    }
                }
                catch (...)
                {
                    std::cout << "Enter a valid input" << std::endl;
                }
            }
            else if (parameters[1] == "3")
            {
                // ISA
                // Can only have one ISA
                try
                {
                    bool ISAunique = true;
                    for (int s = 0; s < openAccounts.size(); s++)
                    {
                        if (openAccounts[s]->toString()[0] == 'I')
                        {
                            std::cout << "Only one ISA account can be created" << std::endl;
                            ISAunique = false;
                        }
                    }
                    if (parameters.size() == 1)
                    {
                        std::cout << "Enter an initial deposit" << std::endl;
                    }
                    else if (ISAunique == true && std::stod(parameters[2]) >= 1000)
                    {
                        Account *a = new Savings(true, std::stod(parameters[2]));
                        openAccounts.push_back(a);
                        viewAccount = -1;
                        std::cout << "ISA created" << std::endl;
                        std::cout << a->toString() << std::endl;
                    }
                    else if (ISAunique == true)
                    {
                        std::cout << "ISA initial balance must be >= \x9C 1000" << std::endl;
                    }
                    else
                    {
                        throw 505;
                    }
                }
                catch (...)
                {
                    std::cout << "Enter a valid input" << std::endl;
                }
            }
            else
            {
                std::cout << "Enter a valid type of account" << std::endl;
            }
        }

        else if (command.compare("view") == 0)
        {
            // display an account according to an index (starting from 1)
            // alternatively, display all accounts if no index is provided
            try
            {

                if (parameters.size() >= 3)
                {
                    std::cout << "Too many commands" << std::endl;
                } // No index entered so all account outputted
                else if (parameters.size() == 1)
                { // Loops through all accounts and outputs them
                    for (int a = 0; a < openAccounts.size(); a++)
                    {
                        std::vector<Transaction> tList = openAccounts[a]->getHistory();
                        std::cout << a + 1 << ") " << openAccounts[a]->toString() << std::endl;
                        // Loops through all transactions and outputs them
                        for (int t = 0; t < openAccounts[a]->getHistory().size(); t++)
                        {
                            std::cout << tList[t].toString();
                        }
                    }
                } // Makes sure input is in range of accounts vector
                else if (stoi(parameters[1]) > 0 && stoi(parameters[1]) < openAccounts.size() + 1)
                {
                    std::vector<Transaction> tList = openAccounts[stoi(parameters[1]) - 1]->getHistory();
                    std::cout << openAccounts[stoi(parameters[1]) - 1]->toString() << std::endl;
                    // Outputs transactions
                    for (int t = 0; t < openAccounts[stoi(parameters[1]) - 1]->getHistory().size(); t++)
                    {
                        std::cout << tList[t].toString();
                    }
                    viewAccount = stoi(parameters[1]) - 1;
                }
                // Statement for if the input is out of range
                else if (stoi(parameters[1]) < 0 || stoi(parameters[1]) > openAccounts.size())
                {
                    std::cout << "Account " << stoi(parameters[1]) << " does not exist" << std::endl;
                }
                // Error message for the rest of errors
                else
                {
                    throw 505;
                }
            }
            catch (...)
            {
                std::cout << "Enter valid input" << std::endl;
            }
        }

        else if (command.compare("withdraw") == 0)
        {
            // allow user to withdraw funds from an account
            try
            { // Condition for if wrong number of commands
                if (parameters.size() == 1)
                {
                    throw int(parameters.size());
                }
                else if (parameters.size() > 2)
                {
                    throw int(parameters.size());
                }
                else if (openAccounts.size() == 0)
                {
                    throw std::string("ERROR: No account created");
                } // Makes sure positive value is entered
                else if (std::stoi(parameters[1]) < 0)
                {
                    throw std::string("ERROR: Enter a positive input");
                }
                else
                {
                    // Decides what account is being viewed
                    int VA = viewingAccount(viewAccount, openAccounts);
                    openAccounts[(VA)]->withdraw(std::stod(parameters[1]));
                }
            }
            // error messages
            catch (int error)
            {
                std::cout << "ERROR: Wrong amount of arguments entered\nNumber of input: " << error << "\nNumber of inputs should be 2" << std::endl;
            }
            catch (std::string error)
            {
                std::cout << error << std::endl;
            }
            catch (...)
            {
                std::cout << "INVALID INPUT" << std::endl;
            }
        }

        else if (command.compare("deposit") == 0)
        {
            try
            {
                // allow user to deposit funds into an account
                if (parameters.size() == 1)
                {
                    throw int(parameters.size());
                }
                else if (parameters.size() > 2)
                {
                    throw int(parameters.size());
                }
                else if (openAccounts.size() == 0)
                {
                    throw std::string("ERROR: No account created");
                }
                else if (std::stoi(parameters[1]) < 0)
                {
                    throw std::string("ERROR: Enter a positive input");
                }
                else
                {
                    // Decides what account is being viewed
                    int VA = viewingAccount(viewAccount, openAccounts);
                    openAccounts[(VA)]->deposit(std::stod(parameters[1]));
                }
            }
            catch (int error)
            {
                std::cout << "ERROR: Wrong amount of arguments entered\nNumber of input: " << error << "\nNumber of inputs should be 2" << std::endl;
            }
            catch (std::string error)
            {
                std::cout << error << std::endl;
            }
            catch (...)
            {
                std::cout << "INVALID INPUT" << std::endl;
            }
        }

        else if (command.compare("transfer") == 0)
        {
            // allow user to transfer funds between accounts
            // i.e., a withdrawal followed by a deposit!

            // Conditions for if wrong number of commands are entered
            if (parameters.size() == 1)
            {
                std::cout << "Enter accounts to transfer between" << std::endl;
            }
            else if (parameters.size() == 3)
            {
                std::cout << "Enter amount to transfer" << std::endl;
            }
            else
            {
                try
                {
                    // Ensures all account are within the account range
                    // Needs to have conditions for all parameters, forces catch statement if characters are entered first in indexes
                    if (std::stoi(parameters[1]) > 0 && std::stoi(parameters[2]) > 0 && std::stoi(parameters[1]) < (openAccounts.size() + 1) && std::stoi(parameters[2]) < (openAccounts.size() + 1))
                    {
                        double oldBalance = openAccounts[std::stoi(parameters[1]) - 1]->getBalance();
                        openAccounts[std::stoi(parameters[1]) - 1]->withdraw(std::stod(parameters[3]));
                        double newBalance = openAccounts[std::stoi(parameters[1]) - 1]->getBalance();
                        // old and new Balance are used to check if the initial withdrawal was succsessful
                        if (newBalance == oldBalance)
                        {
                            std::cout << "Transfer failed as source account does not have enougth balance" << std::endl;
                        } // if withdraw is successful then deposit takes place
                        else
                        {
                            openAccounts[std::stoi(parameters[2]) - 1]->deposit(std::stod(parameters[3]));
                        }
                    }
                    else if (std::stoi(parameters[1]) < 0 || std::stoi(parameters[2]) < 0 || std::stoi(parameters[1]) > (openAccounts.size()) || std::stoi(parameters[2]) > (openAccounts.size()))
                    {
                        std::cout << "Enter numbers within the account list range" << std::endl;
                    }
                } // Catch statement for any other errors, e.g. entering a character
                catch (...)
                {
                    std::cout << "Enter valid inputs" << std::endl;
                }
            }
        }

        else if (command.compare("project") == 0)
        {
            // compute compound interest t years into the future

            // conditions to check size of parameters
            if (parameters.size() == 1)
            {
                std::cout << "Enter years to project" << std::endl;
            }
            else if (parameters.size() >= 3)
            {
                std::cout << "Too many commands" << std::endl;
            }
            else if (openAccounts.size() == 0)
            {
                std::cout << "Create an account to project intrest" << std::endl;
            }
            else
            {
                try
                {
                    int VA = viewingAccount(viewAccount, openAccounts); // sets the viewing account

                    // stops negative value from being projected
                    if (std::stoi(parameters[1]) < 0)
                    {
                        std::cout << "Can't enter negative value" << std::endl;
                    }
                    else if (openAccounts[VA]->toString()[0] == 'S' || openAccounts[VA]->toString()[0] == 'I')
                    {
                        // Need to use dynamic_cast in order to change the type of account
                        // Needs to be done as an Account pointer cannot access a Savings method
                        Savings *tempAccount = dynamic_cast<Savings *>(openAccounts[VA]);
                        tempAccount->computeIntrest(std::stoi(parameters[1]));
                    }
                    // Makes sure that the active account is not a current account
                    else if (openAccounts[VA]->toString()[0] == 'C')
                    {
                        std::cout << "Current account has no interest and cannot be projected" << std::endl;
                    } // any other errors get a standard error message
                    else
                    {
                        throw 505;
                    }
                }
                catch (...)
                {
                    std::cout << "Enter valid inputs" << std::endl;
                }
            }
        }

        else if (command.compare("search") == 0)
        {
            // allow users to search their account history for a transaction
            //(this is a stretch task)

            // Makes sure the parameter size is correct
            if (parameters.size() == 1)
            {
                std::cout << "Enter search value" << std::endl;
            }
            else if (parameters.size() >= 3)
            {
                std::cout << "Too many commands" << std::endl;
            }
            else if (openAccounts.size() == 0)
            {
                std::cout << "Create an account to search" << std::endl;
            }
            else
            {
                try
                {
                    if (std::stoi(parameters[1]) > 0)
                    { // Sets teh viewing account
                        int VA = viewingAccount(viewAccount, openAccounts);
                        // search function
                        search(std::stod(parameters[1]), openAccounts[VA]->getHistory());
                    }
                    else if (std::stoi(parameters[1]) < 0)
                    {
                        std::cout << "Can't enter negative value to search" << std::endl;
                    }
                    else
                    {
                        throw std::string("Enter valid input");
                    }
                }
                // catches any errors
                catch (std::string error)
                {
                    std::cout << error << std::endl;
                }
                catch (...)
                {
                    std::cout << "Enter valid input" << std::endl;
                }
            }
        }

        // Error message to catch any other errors
        else
        {
            std::cout << "ERROR: Invalid input, type 'options' for help" << std::endl;
        }
    }
    std::cout << "End of program, press any key" << std::endl;
    std::getchar();

    // Deleted openAccounts
    for (int i = 0; i < openAccounts.size(); i++)
    {
        delete openAccounts[i];
    }
    // delete []openAccounts;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started:
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
