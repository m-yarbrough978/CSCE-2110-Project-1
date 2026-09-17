#include <iostream>
#include <string>
#include <stack>

using namespace std;

int main(){
  stack<string> cancellationHistory;

  int choice;
  string reservation;

  do {
    cout << "\nCancellation History\n";
    cout << "1. Cancel reservation\n";
    cout << "2. Restore reservation\n";
    cout << "3. Display cancellation history\n";
    cout << "4. Exit\n";
    cout << "Enter choice: ";
    cin >> choice;

    if (choice == 1) {
        cout << "Enter reservation name: ";
        cin >> reservation;

        cancellationHistory.push(reservation);

        cout << reservation << " was cancelled.\n";
    }
    else if (choice == 2) {
        if (cancellationHistory.empty()) {
            cout << "There are no cancelled reservations.\n";
        }
        else {
            cout << cancellationHistory.top()
                 << " was restored.\n";

            cancellationHistory.pop();
        }
    }
    else if (choice == 3) {
        if (cancellationHistory.empty()) {
            cout << "There is no cancellation history.\n";
        }
        else {
            stack<string> temp = cancellationHistory;

            cout << "\nCancellation History:\n";

            while (!temp.empty()) {
                cout << temp.top() << endl;
                temp.pop();
            }
        }
    }
    else if (choice == 4) {
        cout << "Goodbye!\n";
    }
    else {
        cout << "Invalid choice.\n";
    }
  } while (choice != 4);

return 0;
}













