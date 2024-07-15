#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>



class Transaction {
public:
	std::string type;
	double amount;
	Transaction(const std::string& type, const double amount) {
		this->type = type;   // type of transactions --> (withdraw,deposit)
		this->amount = amount; 
	}
};




class BankAccount {
private:
	std::string accountHolderName;
	std::string accountNumber;
	std::string password;
	double balance;
	std::vector<Transaction>transactions; //  it stores the transaction history of each individual or user
public:
	BankAccount() {
		accountHolderName = "";
		accountNumber = "";
		password = "";
		balance = 0;
		transactions.emplace_back("Inital Deposit", 0);
	}
	BankAccount(const std::string& accHolder, const std::string& accNum, const std::string& pwd, const double initBalance) {
		this->accountHolderName = accHolder;
		this->accountNumber = accNum;
		this->password = pwd;
		this->balance = initBalance;
		transactions.emplace_back("Initial Deposit", initBalance);
	}
	void deposit(double amount);
	void withdraw(double amount);
	bool validatePassword(const std::string& pwd);
	void TransactionHistory();
	double CurrentBalance();
};

void BankAccount::deposit(double amount) {
	if (amount <= 0) {
		std::cout << "Invalid Amount " << std::endl;
	}
	else {
		balance += amount;
		transactions.emplace_back("Deposit", amount);
		std::cout << "amount: Rs." << amount << " Deposited Successfully" << std::endl;
		std::cout << "Your Current Balance is Rs." << CurrentBalance() << std::endl;
	}
}

void BankAccount::withdraw(double amount) {
	if (balance < amount) {
		std::cout << "Insufficient Balance " << std::endl;
	}
	else {
		balance -= amount;
		std::cout << "Amount Rs." << amount << " Withdrawn Successfully" << std::endl;
		std::cout << "Your Current Balance is Rs." << CurrentBalance() << std::endl;
	}
}

double BankAccount::CurrentBalance() {
	return balance;
}

bool BankAccount::validatePassword(const std::string& pwd) {
	return (password == pwd);
}

void BankAccount::TransactionHistory() {
	std::vector<Transaction>::iterator transaction;
	for (transaction = transactions.begin(); transaction != transactions.end(); transaction++) {
		std::cout << transaction->type << ": Rs." << transaction->amount << std::endl;
	}
}



// class for Banking System
class BankingSystem {
private:
	std::unordered_map<std::string, BankAccount>accounts;
public:
	void createAccount(const std::string& accHolder, const std::string& accNum, const std::string& pwd, double initBalance);
	BankAccount* accessAccount(const std::string& accNum,const std::string& pwd);
};

void BankingSystem::createAccount(const std::string& accHolder, const std::string& accNum, const std::string& pwd, double initBalance) {
	if (accounts.find(accNum) != accounts.end()) {
		std::cout << "Account Number is Already Exists." << std::endl;
		return;
	}
	if (initBalance <= 0) {
		std::cout << "Minimum Initial deposit amount should be atleast 1 rupee" << std::endl;
		return;
	}
	else {
		BankAccount newAccount(accHolder, accNum, pwd, initBalance);
		accounts[accNum] = newAccount;
		std::cout << "Account Created Successfully" << std::endl;
	}
};

BankAccount* BankingSystem::accessAccount(const std::string& accNum, const std::string& pwd) {
	if (accounts.find(accNum) == accounts.end()) {
		std::cout << "Account Not Found!" << std::endl;
		return nullptr;
	}
	if (!accounts[accNum].validatePassword(pwd)) {
		std::cout << "Invalid Password!" << std::endl;
		return nullptr;
	}
	return &accounts[accNum];
}


int main() {
	BankingSystem abcBank;

	abcBank.createAccount("uday kumar reddy", "987654321", "uday2003", 100000);
	abcBank.createAccount("harsha vardhan", "897654321", "harsha2002", 200000);
	
	BankAccount* account1 = abcBank.accessAccount("987654321", "uday2003");
	if (account1) {
		account1->deposit(1000);
		account1->CurrentBalance();
		account1->withdraw(500);
		account1->deposit(2000);
		account1->deposit(600);
		account1->withdraw(1000);
		account1->TransactionHistory();
	}

	BankAccount* account2 = abcBank.accessAccount("897654321", "harsha2002");
	if (account2) {
		account2->deposit(5000);
		account2->CurrentBalance();
		account2->withdraw(1000);
		account2->TransactionHistory();
	}
	return 0;
}


