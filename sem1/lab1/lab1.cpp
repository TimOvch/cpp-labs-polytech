/*
	� ���������� ���������� ������ ������ ��������� �������� ����� ������ �� �����������
	��� ���������� ������ �������, ������� ������� ��������� ��� ������������������ 
	������������������ ������, ������� ��������� ��������������� �����������������, 
	�������  ��� ���� �� ������������ �������.

	��������� ������������������ �������� ��� ������� �������:
	1. �������� (���������, ���������������� ������ ��������) �������� ����� ���������;
	2. �������������� (Build/Compile  ***.cpp ��� Ctrl+F7)
		���������: ���� ���� ���� �������� �������������, �� ������� ��� ����������� 
			������������, �.�. ��������� ������� ������ (errors) � ��������������
			(warnings), ����������� ��� ���������� ������� ����������� �����;
	3. ����������� ������(Build/Build ***.exe ��� F7)
		��������� 1: ���� ���� ���� ������������, �� ������������ �����������, �.�. 
			��������� ����������������� ������ ���������� ����� � � ������ ����������
			������ ������ ������� ���������� �� ���������� ������������ ���������;
		��������� 2: ����� ���, ��� ������� ������, ������� ���������  � ���, ��� 
			����������� ��� ����� ��������� ���������� ��� ��������� - 
				(Build/Configuration Manager.../Configuration - Debug - ��� ������ �������);
	4. ��������� �� ������������ ��� ������� ��������� ���� ��������(breakpoints) - F9 ��� 
		������ �������� ����� ������� �� ����� ����� ������ ���� ��������������; 
	5. ��������� ��������� � ������ ������� 
		(Debug/Start... ���  F5);

  ���������: ��� ������������� ���� �������� ��������� ���������� ������ � ��������������� 
		������ ����, ������ �� ������ ������� ������� ������� �� �� ����� ����� ������� � 
		������� ������ �� Tool Bar, � ��� ��������� ����� ��������� ��������������.

*/

#include  <iostream>		//��� ������������� ������� �����/������

int nTwin=1;			//���������� ����������
namespace TwinSpace{ int nTwin=2;}	//���������� ��������� �
						//������������ ���� - TwinSpace

#define	  stop	//� ������� ���������������� ������ "������" �������.
				//��� ���������������� ����� ������ ��� ����, �����
				//����� ���� ��������� �� ���� ������ ����� ��������.

int main()
{

 //**********************************************************
	//������� 1. ������ � ����������. ������� ���� ������. �������� ��������� �� �����, 
	//������� �� ���������� ���������� � ��������������� ��������� (�������, ��� 
	//���������� ����, ��������� ��� int, �������-��������).
	//�������� �������� �� ������ ������������� ���������� signed � unsigned ����� ����� 
	//������, � ����� �� ���������� ������������� ������������� ����� �����.

	setlocale(LC_CTYPE, "rus");
	char cByte = 'A'; // �������� ���������� cByte � ���������������� �� ��������� 'A' ���� �� 65
	cByte = cByte + 3; // ������ � ���������� ����� �������� 'D' ��������� ��� char ����� ����������� � �������� �������� � ��� ����� ����� ������� � ������� ASCII, ������� ����� ��������� �������������� �������� ��� ����� ������ �������
	cByte = 0x42; // � ���������� ������ ����� �������� 'B', ������� ����� ����� 66, ��������� 0x42 ��� 66 � ����������������� ������� ���������
	cByte = 42; // � cByte �������� �������� 42 �.�. ������ '*'
	cByte = 66; // � cByte �������� �������� 66 �.�. ������ 'B'
	cByte = 0; // �������� � ���������� 0, ������ �� �������� NULL �.�. ������ ���� ����
	cByte = -0; // -0 �� ���������� �� 0, ������� �������� �����������
	cByte = -1;	// �������� ���� char ����� � ��������� �� -128 �� 127, ������� ������ � ���������� ����� ������ � ��� '\xff';
	cByte = 127; // ������ � ���������� ����� ������ , ����� �������� 127
	cByte = cByte + 1; // �.�. �� ������� �� �������� ���� char ��������� ������������ � �������� ���������� -128 ��� ������ �
	cByte = 128; // ��� �� ������� �� ���� ���� �����, ��� � � ���������� ������. ���������� ������� ���� ������������� � ������� �������� ����� -128 ��� ������ �
	cByte = cByte + 1; // ��� ��� �������, ���� �������� -128, ��������� 1 � ����� -127 ��� ������ �
	cByte = cByte -1; // -127-1=-128 ��� ������ �
	cByte = cByte - 1; // ����� ������������, �� ������ �� ������� �� ������� �������� � �������� 127 � ������ 
	cByte = -128; // �������� -128 � ������ �
	cByte = 127; // ������ � ���������� ����� ������ , ����� �������� 127
	cByte = -127; // �������� -127 ��� ������ �

	unsigned char ucByte = 0x41; // �������� ���������� ucByte ���� unsigned char � ���������������� ��������� 0x41, ������� � ���. ������� ��������� ��������� 65 � ������ 'A'
	ucByte   = 'B'; // �������� 66 � ������ 'B'
	ucByte   =	-1; // �.�. � ���� unsigned char �������� ����� � ��������� �� 0 �� 255, �� ������������ � ������������� � ��������� 255, � ������ �
	ucByte = ucByte + 1; // ��-�� ������������ ��� ����������� � 255 �� �������� 0 � �������� NULL
	ucByte = 255; // ��������� 255 � ������ �
	ucByte = 255 + 1; // ����� ��-�� ������������ ��� ����������� � 255 �� �������� 0 � �������� NULL

	int iInt; // ��������, �� �� ���������������� ���������� iInt
	iInt =  0xffffffff; // � ���������� ����� -1, ��������� ��� int ��������� �������� �� 2 147 483 648 �� 2 147 483 647. ��� �� ������ � ���������� �������� 4 294 967 295, ������ � ����������������� �������, � ���������� ������������ ��� ��� �� -1
	iInt += 1; // ���� -1, ������ 0
	iInt = 16; // ��������� �������� 16
	iInt = 0xABCDEF98; // ������ ����� ��� 2 882 400 152 � �����������������, ��� ������� �� ������� ���� � ������������� ���������� �������� -1 412 567 144

	unsigned int uiInt = 0xffffffff; // �������� ���������� uiInt ���� unsigned int, ������� ��������� � ���� �������� �� 0 �� 4 294 967 295. ����� ����� ���������������� �� ��������� 4 294 967 295 � ����������������� ������� ���������

	float fFloat = 1.f; // �������� ���������� ���� float � ���������������� �� 1
	double dDouble = 1.; // �������� ���������� ���� double � ���������������� �� 1. � ����� float double ���������� ���������, � ����� ��� ����

	// ��������� ��������, ����������� �����. � ������������ ��������,
	// ��� ������� ��������� � ����������. ��������� ������� ����� ���� 
	// ��������� � ���������������.

	double d = 0.1234567890123456789123456789; // � ���������� ��������� 0.12345678901234568, ����� ���������� ���-��� ����� ����� ������� �� �������������� ������ ��� �������� ����� �� 15 �� 17 �������� ���� ����� �������
	d = 2.7; // � ���������� �������� �������� 2.7000000000000002, ��������� ��� ����� ����������� �������� � ��� ���������� ���������� ���������� ����� ����� �������, ��� � �������� � ��������� ������
	float  f = 0.1234567890123456789123456789; // � ���������� �������� �������� 0.123456791, ��������� ������� ������ �� 6 �� 9 ���� ����� �������
	f = 2.7; // �������� 2.70000005 � �������� ����� � ���������� d, �� ��� ����� ����� ������� �������� � ������� ���������� ������

	d	=	1.; // �������� 1
	d	=	0.999999999999999999999999999999999; // ���������� �������� ����� 1, � ���������� �������������� ���������� �������� ����������� �� 1

	stop
	
	// � ������������ �������� ���������, ������������ ���������� sizeof ���
	// ���������� ���� wchar_t (�� ������)
	wchar_t cw = L'A';
	cw = '�';
	size_t n = sizeof(cw); // ������ 4

	stop


// **************************************************************
	//������� 2a. ������� ���������� ����� ������.
	//��������� ������� ���������� ��� ���������� (1) � (2):
	//�������� ���� (�������� � ����) ��������������, ������� ������ ��������� ����������

	iInt=1;
	double dDouble1=iInt/3;		    // (1) �� �������� ��� �� ��� � ������ ����� ������� � �����, ������� ������� 1/3 = 0, � ����� ������������ �������� � ������� ����������
	double dDouble2=iInt/3.;	    // (2) ��� �� �� ������ ������� ������� � ������������� ���� � �������� �� ������������ 3, ����� ���� ��������� �� �������� �����
	double dDouble3=(float)iInt/ 3;	// (3) � ���� �������� �� ������� ������� � ���� �����, ��� � ������� ��������� ������� ����������, �������� �� 3 � ���������� � ����� ����� ������ ������� �����


	// ��������������� ����������.
	// ��������� ����� C ��������� "����������" ������������
	// (��� � ������� (1) � (2)). ��������� ���������� ���������� ����� (1) � (2)
	// (�������� ���������� dDouble, fFloat, nInt, sShort, cByte), ���������� ������� 
	// ��������� ������������ ��� ���������� ������ � ��������� ���������.
	// ��������� ������, ���� ������������ ������� ����������, ��� ��� ������ �� ����������.
	// ��������� (� ������������) �������������� (warnings) �����������.

	short sShort;
	dDouble=fFloat=iInt=sShort=cByte=3.3/3;			// (1) ���������� � ���������� �������������� ���� char �������� �������� 3.3/3=1, ����� ����� �������� 1 ��������� � ���������� sShort ���� short, ����� ����� iInt �������������� � 1, ����� ���������� fFloat ���������������� 1 � ���������� dDouble

	cByte=sShort=iInt=fFloat=dDouble=3.3/3;			// (2) ���������� ��� ���������� dDouble ���� double ���������������� ��������� 1.0999999999999999, ����� ����� ���������� fFloat ���������������� ��� �� ���������, �� ���������� ������� �������� ���� float � ���������� ����������� �������� 1.10000002, ����� ����� ���������������� ���������� iInt � �������� ���������� � �������������� ����, � ������ ������ � 1, ����� ����� ���������� sShort ���������� 1 � ���������� cByte ���� ���������� 1

	//���� ��� ��� ������ "����������" ������������� �������� ���������� �����, ��� ����� 
	// �������� � ������������� ����������� - ��������� (� ������������), � �����?
	// �������� ���� ��������������, ������� ������ ��������� ����������

	iInt	=	257;
	cByte	=	iInt; // � ������ ������ ������������� ����������� �������� ������������ ���������� cByte. ���������� ������ �������� 4-��� �������� ��� � ���� � ����� ������ ������, ������� �������� 257 ���������� 1

	unsigned char cN1=255, cN2=2, cSum;
	cSum = cN1 + cN2; // ��� ���� ���������� ������������. ���������� �������� �������� 257 � 1

	//�������� ���������� ������� � ����������� ����. ��������� (� ������������),
	//������ � ��������� ������ �� ���������� ����� �� ��������� �����
	// �������� ���� ��������������, ������� ������ ��������� ����������
	int iSum = cN1+cN2; // ����� �� ����������, ��������� ���������� � ����� ����� �������� �������� 257 � ������ ����� ����� ���������� ������� ���������� � ������� ����, � ������ ������ ���� int ������� ��� �������� �������� 257

	//��������, ������ ��� �������� ���������� �������� (���������� � �������� �������) 
	// � ������� (1) � (2) ���������� ������ ����������
	// �������� ���� ��������������, ������� ������ ��������� ���������� � ���������,
	// ��� ��� ���� ����������
	char c1=0xff, c2=2;
	unsigned char uc1=0xff, uc2=2;
	int iSum1= c1 + c2;   //(1) ���������� �������� 255, ������� �������� � ���������� �1 ���� char, ����������� � � � c1 ����������� �������� -1 ������� ��� �������� 2+(-1) = 1 
	int iSum2= uc1 + uc2; //(2) � ���� �� ������ �������� 255 �� ����������� ���������� ���� unsigned char � ��� �������� 255+2 = 257 

	stop

	
// ***********************************************************
	//������� 2b. ����� ���������� ����� ������.
	//������������������ ��������� (�������� ���������� dDouble) � ������ (3)
	// �������� ���� ��������������, ������� ������ ��������� ����������
	int nTmp=100, nn=3;
	dDouble=3.3 + (nTmp / nn); // (3) ��� ������� 100/3 � ������������� ����� �� �������� �������� 33, ����� ����� ��� �������� � ��������� 3.3 ������������� ��� ������ ���������� � ���� � ��������� ������ � ������������� � ���������� dDouble 36.299999999999997 

	//�������� ��������� ��� ������ �������� � ������� ��������� ������
	//���������� ����
	dDouble3 = 3.3+((double)nTmp/(double)nn);	// (4) � ���� ������ ��� ���������� � ������� ����� ������ ��������� 36.633333333333333

	stop


// *******************************************************
	// ������� 3. ������� ��������, ������� ��������� �
	//				����� ������������� ����������

	//   � ���� ��������� ���������� ������ ���������� � ����� � ��� �� ������ 
	// nTwin - ���� ����������, ������ ���������� � ����� ������������ ����, 
	// (���������� ���� � ������ ������) ������ - ��������� ������ ������� main(), 
	// ��������� - ��������� ��������� ������ �����. 
	//   � ������ ������� ��������� � ���������� ������ ��������� ����������, � ����� 
	// �� ������� ���������� ���� ���������, � ����� ���� ������������� � ��������� 
	// ��� ���� �������, �������� ����������� � ������� ������� 
	//	��� ���������� ������� ������������� ������������ ������ "Locals" � "Watches"
	// ���������: - � ���� "Watches" ����� ��������� ��� nTwin
	//			��� � ::nTwin, ������� ��� � TwinSpace::nTwin
	

	nTwin=100; // � ���� ������ �� ����������� �������� 100 ���������� ���������� nTwin
	TwinSpace::nTwin = 300; // ��� �� ����������� �������� 300 ���������� nTwin � ������������ ��� TwinSpace
	nTwin++; // ���������� � ���������� ���������� 1

	// �������� �������� �� ��������� "����" ���������. ���� ��������� ���������� nTwin
	// �� ��������� ������ ��� �� ���������� (� ��������� ���� �� ����������), �� �����
	// ��� ��� � ����� ������� main ��� �������� (� ��� �����). ���� ������ �  ���� 
	// "Watches" ��������� ������ nTwin, �� �������� ����� ���������� �������� ����, ��� 
	// �� ����������� ��������� ���������� (���-�� ����� -858993460 ��� 0xcccccccc), 
	// ���� ������ ��������� ���������� �������� ���������� ����������, ����������� �����.
	// ���������� ��� ���� ��� ��������� �����.
	// ���� ���� ������� ������ �������� ���������� ����������, �� ���� ���� ������� � ����
	// "Watches" ���������� ������� ���������, �.�. �������� ��� ::nTwin.
	// ����������: ��� ��� ���� �������� �� ��, ����� �� ��������� ��������� ����.
	int nTwin; // �������� ���������� nTwin ������ ������� main
	nTwin=200; // ��������� �������� 200 ��������� ���������� nTwin
	::nTwin++; // ���������� 1 � ���������� ����������, �� ��� ��� ��������� �������� �������� ::
	{
		int nTwin; // �������� ��������� ���������� ������ �������� ������
		nTwin=-1; // ���������������� ��� ���������� ��������� -1
		::nTwin++; // ��������� � ���������� ���������� 1, �������� ����� 103
		TwinSpace::nTwin++; // ��������� � ���������� nTwin ������ ������������ ���� TwinSpace, �������� ����� 301
	}

	nTwin--; // ����� �� ��������� ���������� nTwin ������ ������� main 1, �������� ����� 199


// *******************************************************
	// ������� 4. ������������ ������ ������ - static
	// �) ��� ������ �������� ����� �������� �������� ��������� nLocal# � nStatic#.
	// �) ��������, ����� ����������� ������������� ����� ����������?
	// �) �������� (� �����������) ������� ����� �������� ������������� 
	//     ���������� nStatic1 � nStatic2 � �������� �������� ������, 
	//     �������� �� ���������� nLocal2.

	for (int i=0; i<3; i++)
	{
		static int nStatic1 = 100;
		int nLocal1 = 100;
		int nLocal2 = 200;
		static int nStatic2 = nLocal2++ * 2;
		nStatic1++;
		nStatic2++;
		nLocal1++;
		stop

	}

/* 1 ��������: ���������������� ����������� ���������� nStatic1 ��������� 100. ���������������� ��������� ���������� nLocal1 � nLocal2, ���������� 100 � 200 �������������. ����������������� ����������� ���������� nStatic2, ��������� 400. � ����� � ���������� nStatic1, nStatic2 � nLocal1 ������������ �������
* 2 ��������: ���������� nStatic1 ��� �� ����������������, ��� �������� �� ��������� 101. nLocal1 � nLocal2 ���������������� ���������� 100 � 200. ������������ nStatic 2 ��� �� ���������������� � �������� �� ��������� 401, � ����� � ���� �� ����������� ����������� 1 � ��������� nLocal2. � ����� � ���������� nStatic1, nStatic2 � nLocal1 ������������ �������
* 3 ��������: nStatic1 �� ����������������, �� �������� 102. nLocal1 = 100 � nLocal2 = 200. Static2 �� ���������������, 1 � nLocal2 �� ������������. � ����� ����� �������� nStatic1 = 103, nStatic2 = 403, nLocal1 = 101, nLocal2 = 200
*/

	// ��������:
	//   �) ��� ���������� ��������� ���������� nStatic1?
	//   �) ��� ��� ���������� ���������������� ?
	for (int i=0; i<3; i++)
	{
		static int nStatic1;
		nStatic1 = 100;
		int nLocal1 = 100;
		nStatic1++;
		nLocal1++;
		stop
	}

	// ���������� nStatic1 � ����� ������ �������� ����� 101, ������ ��� � ������ �������� ��� �������� �� ���������� ���������������� ��������� 100 � � ��� ����� ������������ 1

	
	char ucCounter = 120;
	int q = static_cast<int>(static_cast<char>(ucCounter) + static_cast<char>(5));

	for (unsigned char i = ucCounter; i < ucCounter + 10; i++) // ������� ��� ���������� i �� unsigned char, ����� �������� �� ������������ � ���������� ������������ �����
	{
		static int nStatic1;
		nStatic1 = 100;
		int nLocal1 = 100;
		nStatic1++;
		nLocal1++;
		stop
	}
	
	// �������� ����� ����� �� ��� � � ���������� �����


// *******************************************************
	// ������� 5. ������������ - enum
	// �������� �������� �� ����� � ������� ������������� ��������
	// �������� ������� �� �����, ������� �� ����������, �������
	// ��������� ���������� myColors


	enum eColors
	{
		BLACK,
		BLUE,
		GREEN,
		RED=5,
		YELLOW,
		WHITE=RED+4
	};
	
	eColors   myColors;	//���������� ���������� ���� eColors 
	myColors=BLACK; // �������� 0
	myColors=BLUE; // �������� 1
	myColors=GREEN; // �������� 2
	myColors=RED; // �������� 5
	myColors=YELLOW; // �������� 6
	myColors=WHITE; // �������� 9

	int nnn = BLACK; //����� ������������� ���������� ����� ���������
					 //�������� �� ������ ���������������� ��������

	//����������� ��������� ����� ������������ � ����������:
	nnn = BLUE | YELLOW;
	nnn = BLUE + YELLOW;
	nnn = 1 | 6;

	//���������������� ��������� ������ � ��������
	//�������� ��  ������ ��� ���������� 
	myColors = eColors(1);	//������������� ��������� ����� �������, ����� ���������� �� ������� ������

	// ��������� ��������� ������������ �� ����� ������������ � ��� ���������� myColors?
    myColors = eColors(123);
	stop


// *******************************************************
	// ������� 6.1 ���������� ��� bool
	// �������� ������� �� �����, ������� �� ����������
	// ���������� b � ��������������� ���������. �������� ��� �������� � ������������

	int nNumber = 1;
	bool b = (nNumber != 0); // b = true
	b = (nNumber == 0); // b = false
	b = (nNumber > 0); // b = true
	b = (nNumber > 1); // b = false
	b = 5; // b = true

	//�� ������ ������ ������������� ���������� �������� � ������
	//���� ��� ���������� ����� ��� ������� �������������� (������)
	//�������� ��������: ��� �������������� �������� ���������� ���������� ����������?
	int tmp =  b + 1; // �������� true ���������������� 1, � false 0

	//������� 6.2 � ������������� ��������� (������� �� ��� ����������) ���������� ���
	// ������������ �� ���������� ���������: ���������� �������� ������ ��������� ���,
	// �� ������ ����� ���������� �� ��������, ��� ���� ������ 400-� ��� ��� ���� 
	// ����������. �.�. 1823 - �� ����������, 1824 - ����������, 1900 - �� ����������,
	// 2000 - ����������.
	// �������� �������� ����, ����� ���:
	// ���������� ���������� isLeapYear ��������� �������� true, ���� ���, ��������
	// ���������� year - ����������.
	// ����������: �� ���� ������������ ����������� if-else, ��������� ���������� � switch
	//             ���� �������� ���������� ��������� � ���� ������.
	{
		bool isLeapYear;
		int year = 1823;
		isLeapYear = (year%400==0) || ((year%4 == 0) && (year%100!=0));
		year = 1824;
		isLeapYear = (year%400==0) || ((year%4 == 0) && (year%100!=0));
		year = 1900;
		isLeapYear = (year%400==0) || ((year%4 == 0) && (year%100!=0));
		year = 2000;
		isLeapYear = (year%400==0) || ((year%4 == 0) && (year%100!=0));

		//��������� �������� 
		//bool isLeapYear = (year%400==0) || ((year%4 == 0) && (year%100!=0));
		// ��������� �������� � ���������
		stop
	}

// *******************************************************
	// ������� 7. ����������� const � ����������

	{
		//���������������� ��������� ��� ������� � ��������� (� ������������)
		//������ ��� ���������� 

			//const int nN; // ��������� ������ �������� ��� �������������
			//nN = 1; //
	}



// ********************************************************
	//������� 8. ���������� �������� ��������� � ��������� ���������.

	//������� 8.1 �������� �������� ����, ������� ��������� ��� �������, 
	//���������� � ���������� ch � ��������������� �������.
	//��������� ������������� �������� ��������, ����� ������������ ���� �����
	//��� ����� ������ �������, ������� ������ �� �������������
	//���������: �������� ������ � ��������� ����������� ��������, ��� �������� � �������
	// ����� ASCII ��� ������ ����� ������� �������� �� 0x20 ������ ���� 
	// ��������������� ����� �������� ��������.
	{
		// ����������� �������� ���������� ch � ������� ������ �����
		char ch ;
		std::cin >> ch;
		if(ch >= 65 && ch<=90)
		{
			ch+=32;
			std::cout << ch;
		}
		else if(ch >= 97 && ch<=122)
		{
			ch-=32;
			std::cout << ch;
		}
		else
		{
			std::cout << "�������� ��������";
		}
		//... �������� �������
		// ����� ��������� � ��������� �������� ��� ������ "���" �� �����
		stop
	}


	//������� 8.2 �������� �������� ����, ������� ��������� � ������� if (if/else)
	//��������� ������: ���� x ������ ��� ����� 0, y=0
	//���� x ������ 0 �� ������ 1, �� y=x,
	//���� x ������ ��� ����� 1, �� y=1
	//���������: ������ ���� ������ ��� ����� ���� x � y?
	{
		// � ������ ������ ���������� ������ ����� ��� � ��������� ������, ������� ��� �������� float, double ��� long double.
		double x,y;

		if(x<=0)
		{
			y = 0;
		}
		else if(x>0 && x<1)
		{
			y = x;
		}
		else
		{
			y = 1;
		}
	}

	//������� 8.3 �������� �������� ����, ������� ��������� � ������� switch
	//��������� ������: � ���������� cInput ���� char ���� �������� �������,
	//���������� ����� ��������.
	//���� ������ ������ 'y' (�.�. yes) � ����� ��������, �� ���������
	//���������� � �������� ���������� x
	//���� ������ ������ 'n' (�.�. no) � ����� ��������, �� ���������
	//���������� � �������� (x * 2)
	//���� ����� ������ �����, �� ������� ��������� �� ������
	{
		char cInput;
		int x,y;

		std::cin >> cInput;

		switch(cInput){
			case 'y':
				y = x;
				break;
			case 'Y':
				y = x;
				break;
			case 'n':
			case 'N':
				y = x*2;
				break;
			default:
				std::cout << "�������� ��������";
				break;
		}
		//������������ ��������
		//switch
	}
	// ********************************************************
	//������� 9. �����.

	//������� 9.1 �������� �������� ����, ������� ��������� � ������� for
	//��������� ������: ����� ����� ��������� ��������� ����� �����.
	//������� ������� � ������� ������ ����� ��� � ������� ������� �������.
	//������������� ������ �� ����� ������ ������� ������, ��� �������.
	{
		int start,end,sum=0;

		std::cin >> start >> end;
		
		if (start > end)
		{
			std::cout << "������ ������� ������ �������";
		}
		else
		{
			for(int i = start; i <= end; i++){
				sum+=i;
			}
		}

		//������������ ������� ���������

		//��������� ������������ ��������
		
		// ��������� �����
		// ��������� � ��������� ��������
		stop
	}


	//������� 9.2 �������� �������� ����, ������� ��������� � ������� do-while
	//��������� ������: �� ������ �������� ����� ������ � ������� ����� ��������
	// � �������� ����, ���� �������� ������������� �������: 
	// �������� ������ ��� ����� 10 � ������.
	//���������: �������� �� �������� � �������������� �������� ������� �� �������
	//������ ���������� ����� ������������� ���. ���������� ����������� ��������������
	//�������.
	
	{
		int a;
		do{
			std::cin >> a;
		} while (a&1==0 || a<10);
	}

	//������� 9.3 �������� �������� ����, ������� ��������� � ������� while
	//��������� ������: ������� int x = 0; 
	//�� ������ �������� x=x+1, sum=sum+1/x
	//����� �������� x, ��� ������� sum>1.7
	{
		int x = 0;
		double sum = 0;
		while(sum <= 1.7)
		{
			x++;
			sum += 1.0 / x;
		}

		std::cout << x;
	}
	return 0;
	//��� ���������� ����������
}	// ����� ������� main()

