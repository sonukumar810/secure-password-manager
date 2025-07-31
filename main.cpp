#include <iostream>
#include <mysql.h>
#include <mysqld_error.h>
#include <cstdlib>
#include <cstring>
#include "bcrypt.h"   

using namespace std;

const char *HOST = "localhost";
const char *USER = "root";
const char *PW   = "Sakshi962020";
const char *DB   = "mydb";
#define BCRYPT_HASHSIZE 128

class Login {
private:
	string userId, userPw;
public:
	Login() : userId(""), userPw("") {}
	void setId(string id) { userId = id; }
	void setPw(string pw) { userPw = pw; }
	string getId() const { return userId; }
	string getPw() const { return userPw; }
};

// Bcrypt hash helper
string bcrypt_hash(const string& password) {
	char salt[BCRYPT_HASHSIZE];
	char hash[BCRYPT_HASHSIZE];
	if (bcrypt_gensalt(12, salt) != 0) {
		throw runtime_error("bcrypt_gensalt error");
	}
	if (bcrypt_hashpw(password.c_str(), salt, hash) != 0) {
		throw runtime_error("bcrypt_hashpw error");
	}
	return string(hash);
}

bool bcrypt_verify(const string& password, const string& hash) {
	char hash_out[BCRYPT_HASHSIZE];
	return bcrypt_hashpw(password.c_str(), hash.c_str(), hash_out) == 0 && strcmp(hash, hash_out) == 0;
}

// Fetch hashed password from DB
string DBpw(MYSQL *conn, const string &id) {
	string hashedPW;
	string get = "select pw from password where Id='" + id + "' ";
	if (mysql_query(conn, get.c_str())) {
		cout << "Error: " << mysql_error(conn) << endl;
	} else {
		MYSQL_RES *res = mysql_store_result(conn);
		if (res) {
			MYSQL_ROW row = mysql_fetch_row(res);
			if (row) { hashedPW = row[0]; }
			mysql_free_result(res);
		}
	}
	return hashedPW;
}


int main() {
	Login loginObj;
	MYSQL *conn = mysql_init(NULL);

	if (!mysql_real_connect(conn, HOST, USER, PW, DB, 3306, NULL, 0)) {
		cout << "Error: " << mysql_error(conn) << endl;
		return 1;
	} else {
		cout << "Logged In Db" << endl;
	}
#ifdef _WIN32
	Sleep(3000);
#else
	usleep(3000000);
#endif

	bool exit = false;
	while (!exit) {
		system("cls"); s
		cout << "1. Signup: " << endl;
		cout << "2. Login: " << endl;
		cout << "0. Exit" << endl;
		cout << "Enter your choice : ";
		int val; cin >> val;

		if (val == 1) {  // Signup
			system("cls");
			string id, pw;
			cout << "Enter ID for signup: "; cin >> id;
			loginObj.setId(id);
			cout << "Enter your password: "; cin >> pw;
			loginObj.setPw(pw);

			string hashedPW;
			try {
				hashedPW = bcrypt_hash(loginObj.getPw());
			} catch (const std::exception &e) {
				cout << "Error: " << e.what() << endl;
				continue;
			}

			string Sup = "insert into password(Id,PW) values ('" + loginObj.getId() + "','" + hashedPW + "')";
			if (mysql_query(conn, Sup.c_str())) {
				cout << "Error: " << mysql_error(conn) << endl;
			} else {
				cout << "Signup successfully" << endl;
			}
#ifdef _WIN32
			Sleep(3000);
#else
			usleep(3000000);
#endif

		} else if (val == 2) {  // Login
			system("cls");
			string id, pw;
			cout << "Enter ID for login: "; cin >> id;
			cout << "Enter your password: "; cin >> pw;

			string storedHashedPW = DBpw(conn, id);
			if (!storedHashedPW.empty()) {
				if (bcrypt_verify(pw, storedHashedPW)) {
					cout << endl << "Welcome" << endl;
				} else {
					cout << "Incorrect password \n Try again\n";
				}
			} else {
				cout << "User Id does not exist \n Try Again";
			}
#ifdef _WIN32
			Sleep(5000);
#else
			usleep(5000000);
#endif

		} else if (val == 0) {
			exit = true;
			cout << "Thank you" << endl;
		} else {
			cout << "invalid input" << endl;
#ifdef _WIN32
			Sleep(3000);
#else
			usleep(3000000);
#endif
		}
	}
	mysql_close(conn);
	return 0;
}
