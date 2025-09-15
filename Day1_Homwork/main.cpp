#include <iostream>
#include <Windows.h>
#include <ctime>
#include <cstdlib>

int main()
{
	std::srand(static_cast<unsigned>(std::time(nullptr)));

	while (true) // ���÷��� ����
	{
		int score = 0;
		int choice = 0;

		int game = MessageBoxW(0, L"������ �����Ͻðڽ��ϱ�?", L"������Ÿ��", MB_OKCANCEL | MB_ICONQUESTION);
		if (game != IDOK) {
			MessageBoxW(0, L"������ �����մϴ�.", L"������Ÿ��", MB_OK);
			break;
		}
		MessageBoxW(0, L"������ �����մϴ�.", L"������Ÿ��", MB_OK);

		for (int i = 0; i < 5; i++)
		{
			const wchar_t* title = L"";
			const wchar_t* prompt = L"";
			int successProb = 50;
			int gain = 0;
			int loss = 0;

			if (i == 0) {
				title = L"���� 1��";
				prompt = L"�������ڸ� �߰��ߴ�! ���ڽ��ϱ�?";
				successProb = 80;   gain = 20;  loss = -5;
			}
			else if (i == 1) {
				title = L"���� 2��";
				prompt = L"���Ͱ� ��Ÿ����! �ο�ڽ��ϱ�?";
				successProb = 65;   gain = 50;  loss = -30;
			}
			else if (i == 2) {
				title = L"���� 3��";
				prompt = L"�ٴڿ� ������ ���δ�. �پ�Ѱڽ��ϱ�?";
				successProb = 70;   gain = 10;  loss = -20;
			}
			else if (i == 3) {
				title = L"���� 4��";
				prompt = L"������ ������ ��Ÿ����. ��ȭ�� �ٱ��?";
				successProb = 60;   gain = 15;  loss = -5;
			}
			else {
				title = L"���� ������";
				prompt = L"���� ������ ��Ÿ����! �����ϰڽ��ϱ�?";
				successProb = 55;   gain = 100; loss = -50;
			}

			choice = MessageBoxW(0, prompt, title, MB_OKCANCEL | MB_ICONQUESTION);
			if (choice == IDCANCEL) {
				MessageBoxW(0, L"������ �����߽��ϴ�.", L"�ߵ� ����", MB_OK | MB_ICONEXCLAMATION);
				break;
			}

			int roll = std::rand() % 100;
			int wiggle = std::rand() % 6;
			int gainFinal = gain + (std::rand() % 2 ? wiggle : 0);
			int lossFinal = loss - (std::rand() % 2 ? wiggle : 0);

			if (roll < successProb) {
				score += gainFinal;
				wchar_t msg[128];
				swprintf(msg, 128, L"����! (Ȯ�� %d%%, �ֻ��� %d)\n���� +%d\n���� ����: %d",
					successProb, roll, gainFinal, score);
				MessageBoxW(0, msg, L"���", MB_OK | MB_ICONINFORMATION);
			}
			else {
				score += lossFinal;
				wchar_t msg[128];
				swprintf(msg, 128, L"���С� (Ȯ�� %d%%, �ֻ��� %d)\n���� %d\n���� ����: %d",
					successProb, roll, lossFinal, score);
				MessageBoxW(0, msg, L"���", MB_OK | MB_ICONERROR);
			}
		}

		wchar_t result[128];
		if (score >= 100) {
			swprintf(result, 128, L"����� ������ �������Դϴ�!\n���� ����: %d", score);
		}
		else if (score >= 70) {
			swprintf(result, 128, L"����� ������ ������ Ŭ�����߽��ϴ�.\n���� ����: %d", score);
		}
		else {
			swprintf(result, 128, L"����� �������� Ż���߽��ϴ�. �� ����ϼ���!\n���� ����: %d", score);
		}
		MessageBoxW(0, result, L"���� ����", MB_OK | MB_ICONINFORMATION);

		// ���÷��� ����
		int again = MessageBoxW(0, L"�ٽ� �Ͻðڽ��ϱ�?", L"�絵��", MB_YESNO | MB_ICONQUESTION);
		if (again != IDYES) break; // No�� ��ü ����
	}

	return 0;
}
