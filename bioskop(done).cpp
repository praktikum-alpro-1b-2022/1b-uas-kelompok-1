#include <iostream>
#include<windows.h>
using namespace std;

int colom = 5, baris = 22, total_seat = colom * baris;
int *classes_rows = new int[4]{ 0,4,8,10 };
int *classes_price = new int[4]{ 0,45000,75000,200000 };
bool *cinemaSeats = new bool[total_seat];
int *seatkosong = new int[4]{ 0,4 * colom,8 * colom,10 * colom };


void clearSeats()
{
	for (int i = 0; i <= total_seat; i++)
		cinemaSeats[i] = false;
}


void showAllSeats()
{
	cout << "   -------------THEATER-------------\n----------------------------------------" << endl << endl;
	for (int i = 1; i <= total_seat; i++)
	{
		if (cinemaSeats[i])
			cout <<  i << ",X" << "\t";
		else
			cout <<  i << ",O" << "\t";
		 if (!(i% colom)) cout << endl;
	}
	cout << "----------------------------------------\n    -------------BACK-------------" << endl;
}


int classSeats(int classX)
{
	int sum = 0;
	for (int i = classX; i >= 0; i--)
		sum += classes_rows[i];
	return sum * colom;
}


void showClassSeats(int classX)
{
	int a = classSeats(classX - 1) + 1;
	int b = classSeats(classX);
	cout << "   -------------THEATER-------------\n----------------------------------------" << endl << endl;
	for (int i = a; i <= b; i++)
	{
		if (cinemaSeats[i])
			cout <<  i << ",X" << "\t";
		else
			cout <<  i << ",O" << "\t";
		if ((i % colom)) cout << endl;
	}
	cout << "----------------------------------------\n    -------------BACK-------------" << endl;

}


bool reserveSeat(int seat_no, int classX)
{
	if (!cinemaSeats[seat_no] && seat_no > classSeats(classX - 1) && seat_no <= classSeats(classX))
	{
		cinemaSeats[seat_no] = true;
		seatkosong[classX]--;
		return true;
	}
	return false;
}


bool cancelSeat(int seat_no, int classX)
{
	if (cinemaSeats[seat_no] && seat_no > classSeats(classX - 1) && seat_no <= classSeats(classX))
	{
		cinemaSeats[seat_no] = false;
		seatkosong[classX]++;
		return true;
	}
	return false;
}

void showAbout() {
	cout << endl;
	cout << "||---------------------------------------||" << endl;
	cout << "||-----------BIOSKOPPROJECT -------------||" << endl;
	cout << "||---------------------------------------||" << endl;
	cout << "||-------- MAGROZAN QOBUS ZAIDAN --------||" << endl;
	cout << "||-----  RACHEL MUTHIA PUTRI NASTY ------||" << endl;
	cout << "||------  CINDY AMELIA PRAMESWARI -------||" << endl;
	cout << "||---------------------------------------||" << endl << endl;
	cout << "Press any key to return to main menu" << endl;
}
struct{
    int classX,seatX,tkt_number;
}z;

int main() {
	while (true)
	{    system("color B1");
		int choice;
		cout << "\t\t\t||---------------------------------------||" << endl;
        cout << "\t\t\t||---------------------------------------||" << endl;
        cout << "\t\t\t||-----------  NOW SHOWING --------------||" << endl;
        cout << "\t\t\t||---------------------------------------||" << endl;
        cout << "\t\t\t||--------  1.THE CONJURING      --------||" << endl;
        cout << "\t\t\t||--------  2.BLACK PANTHER 3    --------||" << endl;
        cout << "\t\t\t||--------  3.KKN DESA PENARI    --------||" << endl;
        cout << "\t\t\t||---------------------------------------||" << endl;
		cout << "\nsilahkan pilih :\n1: Pemesanan tiket\n2: pembatalan tiket\n3: Reset semua pesanan\n4: Tampilkan studio\n5: Exit\n\n\n";
		cout << "8: Kelompok 1\n";
		cout << "Input : ";
		cin >> choice;
		int  cancelled = 0;
		bool escape = false;
		system("cls");
		switch (choice)
		{
		case 1:
			cout << "silahkan pilih class apa ?" << endl;
			cout << "1 : Theater 1 (standar class)\n2 : Theater 2 (luxury class)\n3 : Theater 3 (sultan class)" << endl;
			cin >> z.classX;
			system("cls");
			showClassSeats(z.classX);
			cout << " x = sudah dipesan" << endl;
			cout << " O = belum dipesan" << endl;
			cout << "Seats yang tersedia: " << seatkosong[z.classX] << endl;
			cout << "Harga per seat: Rp" << classes_price[z.classX] << endl;
			cout << "Mau pesan berapa tiket ?" << endl;
			cin >> z.tkt_number;
			if (z.tkt_number <= seatkosong[z.classX])
			{
				for (int i = 0; i < z.tkt_number; i++)
				{
					cout << "pilih seat yang ingin di pesan ?" << "  (" << i + 1 << "/" << z.tkt_number << ")" << endl;
					cin >> z.seatX;
					while (!reserveSeat(z.seatX, z.classX))
					{
						cout << "Sorry seat ini tidak tersedia atau sudah di pesan.\nSilahkan masukan seat yang tersedia..." << endl;
						cin >> z.seatX;
					}
					cout << "Successful! Seat: " << z.seatX << " sudah dipesan, Thank you." << endl;
				}
				int total_bayar = classes_price[z.classX] * z.tkt_number;
				int pay;
				cout <<  "Total pembayaran : Rp" << total_bayar << endl;
				cout <<  "Jumlah Bayar     : Rp";cin >> pay;
				cout <<  "Kembalian        : Rp" << pay - total_bayar << endl;
			}
			else
				cout << "Sorry, theater ini sudah penuh.\nReturning to main menu..." << endl;
			break;
		case 2:
			cancelled = 0;
			escape = false;
			cout << "di theater berapa anda ingin mengcancel pemesanan?" << endl;
			cout << "1 : Theater 1 (standar class)\n2 : Theater 2 (luxury class)\n3 : Theater 3 (sultan class)" << endl;
			cin >> z.classX;
			showClassSeats(z.classX);
			cout << "berapa ticket yang ingin di cancel?" << endl;
			cin >> z.tkt_number;
			for (int i = 0; i < z.tkt_number; i++)
			{
				cout << "seat mana yang ingin di cancel?" << "  (" << i + 1 << "/" << z.tkt_number << ")" << endl;
				cin >> z.seatX;
				while (!cancelSeat(z.seatX, z.classX))
				{
					cout << "Sorry seat ini tidak di pesan .\nslahkan pilih seat yang benar... (tekan 0 kembali ke main menu)" << endl;
					cin >> z.seatX;
					if (z.seatX == 0) { escape = true; break; }
				}
				if (escape) break;
				cout << "Successful! Seat: " << z.seatX << " reservation is now cancelled, Thank you." << endl;
				cancelled++;
			}
			cout << fixed << "Total duit yang di kembalikan : Rp" << classes_price[z.classX] * cancelled << endl;
			break;
		case 3:
			cout << "RESETING...\nreservasi theater di reset\nKembali ke main menu..." << endl;
			clearSeats();
			break;
		case 4:
			showAllSeats();
			break;

		case 5:
			return 0;
		case 8:
			showAbout();
			break;
		default:
			cout << "Wrong Choice!\nPlease try again";
			break;
		}
		cin.ignore();cin.get();
		system("cls");
	}
}
