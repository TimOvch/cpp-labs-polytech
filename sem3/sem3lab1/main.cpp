#include <cmath>			// �������������� �������
#include <locale>	// �������, ��������������� ������������ ��������� ��������
#include <iostream>	// ��� - ����� ���������� STL (Standard Template Library)
#include <limits>			// �������� ���������
#include <cfloat>
#include <string>

using namespace std;		// ������������ ��������� ���� STL
#define stop // ��� ���������������� �������� ��������� ����� ��������

int n;	 // ���������� ����������. �� ��������� ��� ����������.

// 2^(1-DBL_MANT_DIG)
// ����� -128 � ��� ��� 0x11111110


void buffer_clear(){
    string trash;
    getline(cin, trash);
}

union byteswap{
    unsigned short num;
    char bytes[2];
};

namespace space	 // � ������������ ���� - space
{
    int n = 1;	 // ��������� ���������� n
}				 // space ���������� ������� ��������� ���� ����������

int  main(){
    setlocale(LC_ALL, "ru_RU.UTF-8");
    // �������� ��������� �� �����, ������� �� ���������� ����������  � ��������������� ���������, �������� ����
    // ����������� ��������. �������� �������� �� ������ ������������� ����������  signed � unsigned ����� ������.
    char c = 'A'; // 65 'A' 0x41
    // � ����������� ������ ������� ���������� ���������� ���������� � �����������������
    // �������� ���������� ����� ���������� ��������� ������. �� ������ ������ �� � ���� Autos.
    c = 0x42;		// 66 'B' 0x42 - 66 �
    c = -1;		// -1 '�' 0xff - 255 ��� ������� � ��������, ��������� � ����� ��� 0, �� ���� 0 ��������
    c = CHAR_BIT;	 // ������ ���������� ���� char
    stop;

    // � ������������ �������� ���������, ������������ ���������� sizeof ���
    // ���������� ���� wchar_t (�� ������)
    //wchar_t cw = '�';
    //size_t ns = sizeof(cw); // ns = 4

    unsigned char uc = 0x41; // 65 'A'
    uc = 'B'; // 66 0x42
    uc = -1; // 255 '\xff'
    stop;

    int i = 1; // 00000000000000000000000000000001
    i = -1; // 11111111111111111111111111111111
    stop;

    unsigned int ui = 1;
    ui = -1; // � �������� �������� �����, ������ ������ ������� �� �������� �� ����

    short s = (short)0xffff;	 // ����� compiler ���������� warning. �������� ���, ����� ������ warning
    s = short(0xffff); // 65535
    s = 1;

    //==== �������� ���, ����� ������ warning
    unsigned short us = (short)0xffff;
    us = 5;

    long l = 0xffffffff; // 8 ����
    l = -128;

    l = FLT_MAX_EXP;	// ��� ��� ��������� �� ������ ����� � ����� limits (float.h) � ��������� �� ����� �� ������������
    //  float 128
    l = DBL_MAX_EXP;
    //  double 1024
    //  ������������ ������� ������ ��� ����� � ��������� ������

    l = FLT_MANT_DIG; // 24
    //  ���������� ���� ��������
    l = DBL_DIG; // 15
    //  ������������ ���������� ���������� ���� � ����� � ��������� ������, ������� ����� ������� �������

    l = FLT_MANT_DIG; // 24
    l = DBL_MANT_DIG; // 53

    float f = -12.5f;	 // ����� warning. ������� ���.
    f = -1.e-27f;

    f = FLT_MAX; // 3.40282347E+38
    f = FLT_MIN; // 1.17549435E-38
    // ������������ � ����������� ����� � ��������� ������

    double d = 0.1234567890123456789123456789; // 0.12345678901234568 18 ��������
    d = -0.123456789012345e+306; // -1.2345678901234499E+305
    d = DBL_MAX; // 1.7976931348623157E+308
    d = DBL_MIN; // 2.2250738585072014E-308
    d = DBL_EPSILON; // ����� ��������� �������� ����� ����� ���-�� ���� double
    // 2.2204460492503131E-16 �������� �������� � ����� ������������� ��������, ������� �������������� ������� ��� ����

    uc = ~0;		 // ��������� ��������� 255 '\xff'
    i = ~0; // -1 (��� ������� � �������� �������������)
    stop;
    // ������ (��� ����������) ��� ������� ���������� ����� ������
    // ��������� �� ��������, ������� �� ���������� � ���� Autos. ���������� ������� ��������� ������������.
    d = f = i = s = c = 1 / 3; // � = 0    s = 0   i = 0    f = 0   d = 0
    c = s = i = f = d = 100 / 3; // � = 33    s = 33   i = 33    f = 33   d = 33
    c = s = i = f = d = 10 / 3; // � = 3    s = 3   i = 3    f = 3   d = 3
    c = s = i = f = d = 1 / 3.; // // � = 0    s = 0   i = 0    f = 0.333333343   d = 0.33333333333333331
    // ������������ ����������� ������ ������. � 3 �������� ��� �������� ������������� � ������� ��� ������� ������� ����� �������������. 3. - ��� double

    // ������ "����������" ������������� �������� ���������� �����.	 ��������� ����������.
    i = 256;
    c = i; // c = 0 �.�. i = 0b100000000, ��� �������� ���������� �������� ������ ���� � ����������  c = 0b00000000

    uc = 255;
    unsigned char u = 2, sum = uc + u; // 0b11111111 + 0b10 = 0b100000001 ��� ���������� � ��� ���������� ������ ��� � ���������� 1
    stop;

    // ����� ���������� �����	��������� ������� ����������� � ������� (3) � (4)
    i = 100;
    f = d = i / 3;							// (3) f = 33
    f = d = (double)i / 3;		// (4) f = 33.3333321   d = 33.333333333333336
    f = d = double(i) / 3;			// (4) f = 33.3333321   d = 33.333333333333336
    f = d = static_cast<double>(i) / 3;		// (4) f = 33.3333321   d = 33.333333333333336
    stop;

    // ������� ��������, ������� ��������� � ����� �������������. � ���� ��������� ���������� ������
    //  ���������� � ����� � ��� �� ������ n.  ���� - ����������, ������ ���������� � ����� ������������ ����,
    // ������ - ��������� ������ ������� main(), ��������� - ��������� ������ �����.
    //  �������� ��������, ��� ���������� ���������� � ��, ��� � ������������ ���� space - ��������� ��� ������� main()
    // ����������, � ����� �� ������� ���������� ���� ���������, c������������ ������� �������� � ������� ���������
    // ������ ����������. ��� ���������� ������� ������������� ������������  ��������� "Watches" ��� "Locals" ����
    // "Autos". ���������: � ���� "Watches" ����� ��������� ����� ��� ���������� (n, ::n, � space::n)
    n = 100; // ����������
    space::n = 200; // ������ space
    n++; // ����������
    int n;		//��� ����� ��� ���������� ? ������ main
    n = 10; // main
    ::n++; // ����������

    {				//  ������ �����
        int n;		// ��� ���������� ����� ������ �����
        n = -1; // ������ �����
        n++; // ������ �����
        ::n++; // ����������
        space::n++; // ������ space
    }		// ����� �����
    n--; // main
    ::n--; // ����������
    space::n--; // main

    // ������������ ������ ������ - static �������� ������� �� �����, �������� �������� ��  ������ ���������
    // ���������� nLoc � nStat
    {
        Again:
        int outer;
        for (int i = 0; i < 5; i++)
        {
            static int nStat;
            {
                int nLoc = 0;
                nLoc++;		nStat++;
            }
            outer = nStat;
        }
        if (outer < 10)
            goto Again;
    }
    // ������������ - enum. �������� �������� �� ����� � ������� ������������� ��������
    enum RANK
    {
        One, // 0
        Two, // 1
        Three, // 2
        Four, // 3
        Jack = 6, // 6
        Queen, // 7
        Ace = Queen + 3, // 10
        Joker = 20// 20
    };
    typedef RANK RANG;

    RANG r = Jack;
    if (r == Jack)
        r = Queen;

    if (r == Queen)
    {
        // ����� ������������� ���������� ����� ��������� enum-����������
        int i = r;
        r = RANK(i++);		// �������� �������������� ���� ��������� ����
        i = r;
        r = RANK(++i); // r = 8
        i = r;
    }
    RANK rr = Ace;
    stop;
    //	���������� ��� bool.	�������� ������� �� �����, ������� �� ���������� ���������� b
    {
        int n = 127;
        bool b = n != 0; // 1
        b = n == 0; // 0
        b = n > 0; // 1
        b = n <= 0; // 0
        b = n > 1; // 1

        int num = static_cast<int>(b); // 1
        if (b)
            cout << "\n\t My flag is: true" << "   or: " << b
                 << "\n\t Conversion to int: " << num << endl;
        b = n == num;
        cout << "\n\t Now the flag is: false" << "   or: " << b;
    }

    //	����������� const
    const double pi = acos(-1.);
    double space_permiability = 4.e-7 * pi;		//	��������� ������������� �������
    const int dozen = 12;
    int var = dozen;

    //	���������������� ��������� ������� � ��������� ������ ���������� (l-value �������� left value)
    //	dozen = 1; ������� � ������������� �� ����� ���� �������� ����� ���������� � ��������������
    //	��������� �������� ����������. ��������� ��������, ������� ��������� ���������� version.
    //	��� ����� ������� ��� ����, ����� ��������� ��� ������?
     //������� �������� ������� � ��������� MSVER400 � ������� � ��������� MSVER400 ��� �� ���������

#define MSVER400
    const char* version;
#if defined MSVER400
    version = "version 4.00";
#elif defined MSVER311
    version = "version 3.11";
#else
	version = "version Unknown";
#endif

    cout << endl << version;
    stop;

    //� ���� ClassView ��� Solution Explorer ��������� ����� �� ��� ������� ����� ������� Project/Properties.
    //	� ������� Property Pages �������� �� ����� Configuration Properties, ���������, ��� � ������� Code Generation
    //	����������� ��������� ���������� _DEBUG. �������� ��������� ������������� � ��� �++, �������
    //	� ����������� �� ����������� ������������ ������� (_DEBUG ��� NDEBUG) ������� ���������������
    //	���������. �������� ������������ ������� (� ������� Property Pages) � ��������� ��� ���.
    //	����� �������� ������������ ����������� ������� Configuration Manager

#if defined DEBUG
    cout << endl << "Debug" << endl;
#else
    cout << endl << "Release" << endl;
#endif


    //	���������� �����. ��������� ���� �������������.
    {
        // ���� while ���� ������������, ����� ���������� ���������� �������� (����������) �����.
        cout << "\n\nGradually eat out all the units:\n\n";
        unsigned short us = 0xff;
        while (us)
        {
            cout << hex << us << endl;
            us &= us - 1;
        }
        cout << hex << us << "\nDone\n";
        // ���� for ���� ������������, ����� �������� ���������� �������� �/��� ���� ��� ����������.
        // ���������: odd - �������, even - ������.
        cout << "\n\nShow even-odd:\n\n";
        for (int i = 0; i < 10; i++)
        {
            if (i & 1)
                cout << i << " - odd\n";
            else
                cout << i << " - even\n";
        }
        // ����� ����� ������������ ���� do-while?
        char c = ' ';
        do
        {
            if (c == 'a')
                cout << "\nAction is a delegate type in C#";
            else if (c == 'b')
                cout << "\nbreak is one of the 'leave' statements in all C-like languages";
            else if (c == 'c')
                cout << "\ncontinue is a 'go on' statement in all C-like languages";
            else if (c == 'd')
                cout << "\ndo-while is a rarely used loop statement in all C-like languages";
            else
                cout << "\nPlease read the rules of this loop";
            cout << "\n\nEnter chars: a, b, c, d (q - to quit):\n\n";
            cin >> c;
            if (c == 'q')
                cout << "\nI am going to leave the loop\n";
        } while (c != 'q');
        stop;
    }
    //	���������� �������� ��������� � �����. ������� y = f(x) ������ ��������
    //	�������� �������� ����, ������� � ����� 0.1 ��������� y = f(x)  � ������� � ���������� ���� �������� x � y.
    //	  y
    //	  |
    //	 2|__________
    //	  |         /\
	//	  |        /  \
	//	  |       /    \
	//	  |______/      \__________  x
    //	  0      1   2   3
    //	 ���������� 2 �������� ����� ���������:   1. ����������� ��������� if	 2. ����������� ��������� ��������    ? :

    // �������� if:

    double k = 0;

    for (int j = 0; j<=35; j+=1){
        k = (double)j/10;
        if(k>1 && k<=2){
            cout << 2*k-2 << endl;
        } else if(k>2 && k<3){
            cout << -2*k+6 << endl;
        } else{
            cout << 0. << endl;
        }
    }

    cout << "\n\n";

    // ������������ ��������

    for (int j = 0; j<=35; j+=1){
        k = (double)j/10;
        cout << ( (k<=1 || k>=3) ? ( 0. ) : ( (k<2) ?  ( 2*k-2) : (-2*k+6) ) ) << endl;
    }

    cout << "\n\n";

    //	�������� ��������, ������� � ������� for � switch ��������� ��������� ������. ���� ������������ ����:
    //	������ 'a',   ��� �������� �������  "Ok" (� ��������)
    //	������ 'b',   ��� �������� �������  Bell (alert - �������� ������)
    //	������ '�',   ��� �������� �������  �����, ������� ����� ���������� ��������� ��������
    //	������ 'Esc', ��� �������� �������  "to quit use 'q'"
    //	������ 'q',   ��� �������� �������  "Bye" � ������� �� ����� �����

    int counter = 0;

    cout << "Enter value: ";
    for(char p = 0; p != 'q'; cin >> p){
        ++counter;
        switch (p) {
            case 'a':
                cout << "\"Ok\"" << endl;
                break;
            case 'b':
                cout << '\a' << endl;
                break;
            case 'c':
                cout << "Number of entries: " << counter << endl;
                break;
            case 27: // 27 ASCII
                cout << "to quit use \'q\'" << endl;
                continue;
            default:
                cout << endl;
                continue;

        }
        buffer_clear();
        fflush(stdin);

        cout << "Enter value: ";
    }

    //	��������� ��������:  |, &, ~, ^ � ������ >>, <<
    //	��������� ������� ����� ���������� flags � �������� ��������� � ��������� ���� unsigned short flags = 0xaabb;
    //	��� ���
    unsigned short flags = 0xaabb;

    unsigned short swapped = ((flags & 0x00FF) << 8) | ((flags & 0xFF00) >> 8);

    cout <<"\n bits = " << hex << swapped;

//    byteswap swap = {};
//    swap.num = flags;
//
//    char temp = swap.bytes[0];
//    swap.bytes[0] = swap.bytes[1];
//    swap.bytes[1] = swap.bytes[0];


    //	��� ������ � ����������������� ���� �����������  cout <<"\n bits = " << hex << flags;
    //	� ���������� unsigned char byte = 0x26;
    //      - ���������� � ������� 3-� ��� (���� �� ����). �������� ���������.
    //	- ������������ ��� ������� ����. �������� ���������.
    //      - �������� 4 ������� ����. �������� ���������.

    char byte = 0x26;
    byte = byte|0b1000;
    cout <<endl << hex << (int)byte << endl<<dec<< (int)byte;

    byte = byte^0b00000011;
    cout <<endl << hex << (int)byte << endl<<dec<< (int)byte;

    byte = byte&0xF0;
    cout <<endl << hex << (int)byte << endl<<dec<< (int)byte;

    //	cout <<endl << hex << flags << endl<<dec<<flags;
    cout << "\n\n";
}	// ����� ������� main()
