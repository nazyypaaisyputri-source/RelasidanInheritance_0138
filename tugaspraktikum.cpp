#include <iostream>
#include <vector>
#include <string>

using namespace std;

class User {
public:
    static int globalId; 
    int id;
    string nama;
    string email;

    User(string pNama, string pEmail) : nama(pNama), email(pEmail) {
        id = generateId();
    }

    int generateId() {
        return ++globalId;
    }
};

int User::globalId = 0;

class Member : public User {
public:
    bool status; 

    Member(string pNama, string pEmail) : User(pNama, pEmail) {
        status = true; 
    }

    void showProfile() {
        cout << "--- Profil Member ---" << endl;
        cout << "ID     : " << id << endl;
        cout << "Nama   : " << nama << endl;
        cout << "Email  : " << email << endl;
        cout << "Status : " << (status ? "Aktif" : "Non-Aktif") << endl;
        cout << "---------------------" << endl;
    }
};

class Admin : public User {
public:
    Admin(string pNama, string pEmail) : User(pNama, pEmail) {}

    // Menggunakan const & agar efisien (tidak copy data) dan aman
    void showAllMember(const vector<Member>& daftarMember) {
        cout << "\n=== Daftar Semua Member (Oleh Admin: " << nama << ") ===" << endl;
        for (const auto& m : daftarMember) {
            cout << "ID: " << m.id << " | Nama: " << m.nama 
                 << " | Status: " << (m.status ? "Aktif" : "Non-Aktif") << endl;
        }
        cout << "======================================================" << endl;
    }

    void toggleActivationMember(Member& m) {
        m.status = !m.status;
        cout << "\n[Sistem] Status Member " << m.nama << " berhasil diubah." << endl;
    }
};

int main() {
    Admin adminUtama("Nazypa", "nazypa@admin.com");

    vector<Member> listMember;
    listMember.push_back(Member("Andi", "andi@mail.com"));
    listMember.push_back(Member("Budi", "budi@mail.com"));

    listMember[0].showProfile();

    adminUtama.showAllMember(listMember);
    adminUtama.toggleActivationMember(listMember[1]);
    adminUtama.showAllMember(listMember);

    return 0;
}