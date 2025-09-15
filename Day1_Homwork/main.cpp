#include <iostream>
#include <Windows.h>
#include <ctime>
#include <cstdlib>

int main()
{
	std::srand(static_cast<unsigned>(std::time(nullptr)));

	while (true) // 리플레이 루프
	{
		int score = 0;
		int choice = 0;

		int game = MessageBoxW(0, L"게임을 시작하시겠습니까?", L"선택판타지", MB_OKCANCEL | MB_ICONQUESTION);
		if (game != IDOK) {
			MessageBoxW(0, L"게임을 종료합니다.", L"선택판타지", MB_OK);
			break;
		}
		MessageBoxW(0, L"게임을 시작합니다.", L"선택판타지", MB_OK);

		for (int i = 0; i < 5; i++)
		{
			const wchar_t* title = L"";
			const wchar_t* prompt = L"";
			int successProb = 50;
			int gain = 0;
			int loss = 0;

			if (i == 0) {
				title = L"던전 1층";
				prompt = L"보물상자를 발견했다! 열겠습니까?";
				successProb = 80;   gain = 20;  loss = -5;
			}
			else if (i == 1) {
				title = L"던전 2층";
				prompt = L"몬스터가 나타났다! 싸우겠습니까?";
				successProb = 65;   gain = 50;  loss = -30;
			}
			else if (i == 2) {
				title = L"던전 3층";
				prompt = L"바닥에 함정이 보인다. 뛰어넘겠습니까?";
				successProb = 70;   gain = 10;  loss = -20;
			}
			else if (i == 3) {
				title = L"던전 4층";
				prompt = L"수상한 상인이 나타났다. 금화를 줄까요?";
				successProb = 60;   gain = 15;  loss = -5;
			}
			else {
				title = L"던전 보스방";
				prompt = L"최종 보스가 나타났다! 도전하겠습니까?";
				successProb = 55;   gain = 100; loss = -50;
			}

			choice = MessageBoxW(0, prompt, title, MB_OKCANCEL | MB_ICONQUESTION);
			if (choice == IDCANCEL) {
				MessageBoxW(0, L"모험을 포기했습니다.", L"중도 종료", MB_OK | MB_ICONEXCLAMATION);
				break;
			}

			int roll = std::rand() % 100;
			int wiggle = std::rand() % 6;
			int gainFinal = gain + (std::rand() % 2 ? wiggle : 0);
			int lossFinal = loss - (std::rand() % 2 ? wiggle : 0);

			if (roll < successProb) {
				score += gainFinal;
				wchar_t msg[128];
				swprintf(msg, 128, L"성공! (확률 %d%%, 주사위 %d)\n점수 +%d\n현재 점수: %d",
					successProb, roll, gainFinal, score);
				MessageBoxW(0, msg, L"결과", MB_OK | MB_ICONINFORMATION);
			}
			else {
				score += lossFinal;
				wchar_t msg[128];
				swprintf(msg, 128, L"실패… (확률 %d%%, 주사위 %d)\n점수 %d\n현재 점수: %d",
					successProb, roll, lossFinal, score);
				MessageBoxW(0, msg, L"결과", MB_OK | MB_ICONERROR);
			}
		}

		wchar_t result[128];
		if (score >= 100) {
			swprintf(result, 128, L"당신은 던전의 정복자입니다!\n최종 점수: %d", score);
		}
		else if (score >= 70) {
			swprintf(result, 128, L"당신은 던전을 무사히 클리어했습니다.\n최종 점수: %d", score);
		}
		else {
			swprintf(result, 128, L"당신은 던전에서 탈출했습니다. 더 노력하세요!\n최종 점수: %d", score);
		}
		MessageBoxW(0, result, L"게임 종료", MB_OK | MB_ICONINFORMATION);

		// 리플레이 묻기
		int again = MessageBoxW(0, L"다시 하시겠습니까?", L"재도전", MB_YESNO | MB_ICONQUESTION);
		if (again != IDYES) break; // No면 전체 종료
	}

	return 0;
}
