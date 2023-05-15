#include <iostream>
#include <ctime>
#include <fstream>
#include<string>
#include <sstream>
#include <time.h>
#include <chrono>
using namespace std;

int main()
{
    setlocale(LC_ALL, "ru");
    ifstream fin("in.txt");
    if (fin.is_open()) {
        string strh;
        string str[100];
        int l = 1;
        getline(fin, strh);
        str[0] = strh;
        if (fin.eof() && strh.empty()) {
            cout << "Empty" << endl;
        }
        else {
            while (!fin.eof()) {
                getline(fin, strh);
                str[l] = strh;
                l++;
            }
            for (int d = 0; d < l; d++) {
                istringstream ss(str[d]);
                int* mas = new int[10000000];
                int* mas2 = new int[10000000];
                unsigned long int n = 0;
                while (ss >> mas[n++])
                    ;
                n--;
                for (int i = 0; i < n; i++) {
                    mas2[i] = mas[i];
                }
                if (n > 1) {
                    int cnt = 0;
                    int temp, item;
                    auto start = chrono::high_resolution_clock::now();
                    for (int counter = 1; counter < n; counter++)
                    {
                        temp = mas2[counter];
                        item = counter - 1;
                        while (item >= 0 && mas2[item] > temp)
                        {
                            mas2[item + 1] = mas2[item];
                            mas2[item] = temp;
                            item--;
                            cnt++;
                        }
                    }
                    for (int i = 0; i < n; i++) {
                        cout << mas2[i] << " ";
                    }
                    auto end = chrono::high_resolution_clock::now();
                    cout << "Количество перстановок: " << " " << cnt << "/";
                    cout << std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() << endl << "наносекунд" << std::endl;
                    int cnt2 = 0;
                    start = chrono::high_resolution_clock::now();
                    for (int s = n / 2; s > 0; s /= 2) {
                        for (int i = s; i < n; ++i) {
                            for (int j = i - s; j >= 0 && mas[j] > mas[j + s]; j -= s) {
                                int temp = mas[j];
                                mas[j] = mas[j + s];
                                mas[j + s] = temp;
                                cnt2++;
                            }
                        }
                    }
                    end = chrono::high_resolution_clock::now();
                    cout << endl << "Количество перстановок: " << n << "  " << cnt2 << "/";
                    cout << std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() << endl << "наносекунд" << std::endl;
                    for (int i = 0; i < n; i++) {
                       cout << mas[i] << " ";
                    }
                    cout << endl;
                }
                else {
                    cout << "Массив невозможно отсортировать так как он содержит всего 1 элемент";
                }
                delete mas;
            }
        }
    }
    else {
        cout << "Невозможно открыть файл";
    }

    return 0;
}