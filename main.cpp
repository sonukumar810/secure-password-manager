#include <iostream>
#include <mysql.h>
#include <mysqld_error.h>
#include <cstdlib> // system()
using namespace std;

const char *HOST = "localhost";
const char *USER = "root";
const char *PW = "Sakshi962020";
const char *DB = "mydb";

class Login
{
private:
	string userId, userPw;

public:
	Login() : userId(""), userPw("") {};

	void setId(string id)
	{
		userId = id;
	}
	void setPw(string pw)
	{
		userPw = pw;
	}

	string getId() const
	{
		return userId;
	}

	string getPw() const
	{
		return userId;
	}
};
char encryptCh(char ch, int shift)
{
	if (isalpha(ch))
	{
		char base = isupper(ch) ? 'A' : 'a';
		char encrypted_ch = (ch - base + shift + 26) % 26 + base;
		return encrypted_ch;
	}
	if (isdigit(ch))
	{
		char encrypted_ch = (ch - '0' + shift + 10) % 10 + '0';
		return encrypted_ch;
	}

	return ch;
}
string encrypt(const string &password, int shift)
{
	string encrypted = "";
	for (int i = 0; i < password.length(); i++)
	{
		char ch = password[i];
		char encryptedChar = encryptCh(ch, shift);
		encrypted += encryptedChar;
	}
	return encrypted;
}

char decryptCh(char ch, int shift)
{
	if (isalpha(ch))
	{
		char base = isupper(ch) ? 'A' : 'a';
		char decrypted_ch = (ch - base - shift + 26) % 26 + base;
		return decrypted_ch;
	}
	if (isdigit(ch))
	{
		char decrypted_ch = (ch - '0' - shift + 10) % 10 + '0';
		return decrypted_ch;
	}
	else
	{
		return ch;
	}
}

string decrypt(const string &encrypted, int shift)
{
	string decrypted = "";
	for (int i = 0; i < encrypted.length(); i++)
	{
		char ch = encrypted[i];
		char decryptedChar = decryptCh(ch, shift);
		decrypted += decryptedChar;
	}
	return decrypted;
}

string DBpw(MYSQL *conn, const string &id)
{
	string encryptedPW;

	string get = "select pw from password where Id='" + id + "' ";
	if (mysql_query(conn, get.c_str()))
	{
		cout << "Error: " << mysql_error(conn) << endl;
	}
	else
	{
		MYSQL_RES *res;
		res = mysql_store_result(conn);
		if (res)
		{
			MYSQL_ROW row = mysql_fetch_row(res);
			if (row)
			{
				encryptedPW = row[0];
			}
		}
	}
	return encryptedPW;
}

int main()
{
	Login loginObj;

	MYSQL *conn;
	conn = mysql_init(NULL);

	if (!mysql_real_connect(conn, HOST, USER, PW, DB, 3306, NULL, 0))
	{
		cout << "Error: " << mysql_error(conn) << endl;
	}
	else
	{
		cout << "Logged In Db" << endl;
	}
	Sleep(3000);
	int shift = 3;
	bool exit = 0;
	while (!exit)
	{
		system("cls");
		cout << "1. Signup: " << endl;
		cout << "2. Login: " << endl;
		cout << "0. Exit" << endl;
		cout << "Enter your choice : ";
		int val;
		cin >> val;
		if (val == 1)
		{
			system("cls");
			string id, pw;
			cout << "Enter ID for signup: ";
			cin >> id;
			loginObj.setId(id);

			cout << "Enter your password: ";
			cin >> pw;
			loginObj.setPw(pw);

			string encryptedPW = encrypt(loginObj.getPw(), shift);

			string Sup = "insert into password(Id,PW) values ('" + loginObj.getId() + "','" + encryptedPW + "')";
			if (mysql_query(conn, Sup.c_str()))
			{
				cout << "Error: " << mysql_error(conn) << endl;
			}
			else
			{
				cout << "Signup successfully" << endl;
			}
			Sleep(3000);
		}
		else if (val == 2)
		{
			system("cls");

			string id, pw;
			cout << "Enter ID for signup: ";
			cin >> id;

			cout << "Enter your password: ";
			cin >> pw;

			string getDB = DBpw(conn, id);
			if (!getDB.empty())
			{
				string decryptedPW = decrypt(getDB, shift);
				if (decryptedPW == pw)
				{
					cout << endl;
					cout << "Welcome" << endl;
				}
				else
				{
					cout << "Incorrect password \n Try again\n";
				}
			}
			else
			{
				cout << "User Id doesnt exist \n Try Again";
			}
			Sleep(5000);
		}
		else if (val == 0)
		{
			exit = true;
			cout << "Thank you" << endl;
		}

		else
		{
			cout << "invalid input" << endl;
			Sleep(3000);
		}
	}
	mysql_close(conn);

	return 0;
}
