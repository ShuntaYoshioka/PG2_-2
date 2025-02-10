#include <Novice.h>
#include <ctime>
#include "Player.h"
#include "Enemy.h"


const char kWindowTitle[] = "LC1C";

enum SCENE {
	TITLE,
	GAME,
	CLEAR,
	GAMEOVER
};

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };


	//宣言
	srand(static_cast<unsigned int>(time(0)));

	Player* player = new Player(600, 300, 8, 8);

	Enemy enemies[16];
	for (int i = 0; i < 16; i++) {
		enemies[i] = Enemy(1280 + i * 160, rand() % 720, 5, 0);
	}

	int enemyKillCount = 0;
	SCENE scene = TITLE;

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///

		//タイトル
		if (scene == TITLE) {

			//リセット
			enemyKillCount = 0;
			for (int i = 0; i < 16; i++) {
				enemies[i] = Enemy(1280 + rand() % 201, rand() % 720, 5, 0);
			}
			if (keys[DIK_SPACE]) {
				scene = GAME;
			}

			Novice::ScreenPrintf(200, 300, "press space");
		}

		//ゲーム本編
		if (scene == GAME) {
			player->Move(keys);
			player->Update();

			for (int i = 0; i < 16; i++) {
				enemies[i].Update();

				// 弾と敵の衝突判定
				for (int j = 0; j < 25; j++) {
					if (player->bullets_[j].isShot_) {
						int bx = player->bullets_[j].posX_;
						int by = player->bullets_[j].posY_;
						int er = enemies[i].GetRadius();
						int ex = enemies[i].GetPosX();
						int ey = enemies[i].GetPosY();

						int dx = bx - ex;
						int dy = by - ey;

						if (dx * dx + dy * dy <= er * er) {
							player->bullets_[j].isShot_ = false;
							enemyKillCount++;

							enemies[i] = Enemy(1280 + rand() % 500, rand() % 720, 5, 0);
						}
						if (enemyKillCount >= 40) {
							scene = CLEAR; //クリア
						}
					}
				}

				//自機と敵の衝突判定
				int px = player->GetPosX();
				int py = player->GetPosY();
				int playerRadius = 16;

				int ex = enemies[i].GetPosX();
				int ey = enemies[i].GetPosY();
				int enemyRadius = enemies[i].GetRadius();

				int dx = px - ex;
				int dy = py - ey;

				if (dx * dx + dy * dy <= (playerRadius + enemyRadius) * (playerRadius + enemyRadius)) {
					//ダメージ
					player->TakeDamage(1);
					if (player->GetHP() <= 0) {
						scene = GAMEOVER; //ゲームオーバー

					}

					//敵リセット
					enemies[i] = Enemy(1280 + rand() % 500, rand() % 720, 5, 0);
				}
			}

			//描画
			player->Draw();
			for (int i = 0; i < 16; i++) {
				enemies[i].Draw();
			}
		}


		//ゲームオーバー


		if (scene == GAMEOVER) {
			Novice::ScreenPrintf(200, 300, "GAMEOVER [F]  TITLE");
			if (keys[DIK_F]) {
				scene = TITLE;
			}
		}
		//クリア
		if (scene == CLEAR) {
			Novice::ScreenPrintf(200, 300, "CLEAR  [F]  TITLE ");
			if (keys[DIK_F]) {
				scene = TITLE;
			}
		}

		///
		/// ↑更新処理ここまで
		///



		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	delete player;

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}