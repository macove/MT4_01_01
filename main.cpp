#include <Novice.h>
#include "GeometryUtility.h"

const char kWindowTitle[] = "学籍番号";

GeometryUtility geometryUtility;

static const int kRowHeight = 20;
static const int kColumnWidth = 60;

Matrix4x4 MakeRotateAxisAngle(const Vector3& axis, float angle) {

	Vector3 n = geometryUtility.normalize(axis);

	float cosTheta = cosf(angle);
	float sinTheta = sinf(angle);
	float oneMinusCosTheta = 1.0f - cosTheta;

	float nx = n.x;
	float ny = n.y;
	float nz = n.z;

	Matrix4x4 result = {
		nx * nx * oneMinusCosTheta + cosTheta,          nx * ny * oneMinusCosTheta + nz * sinTheta, nx * nz * oneMinusCosTheta - ny * sinTheta, 0.0f,
		nx * ny * oneMinusCosTheta - nz * sinTheta,     ny * ny * oneMinusCosTheta + cosTheta,      ny * nz * oneMinusCosTheta + nx * sinTheta, 0.0f,
		nx * nz * oneMinusCosTheta + ny * sinTheta,     ny * nz * oneMinusCosTheta - nx * sinTheta, nz * nz * oneMinusCosTheta + cosTheta,      0.0f,
		0.0f,                                          0.0f,                                      0.0f,                                      1.0f
	};
	return result;
}

void MatrixScreenPrintf(int x, int y, const Matrix4x4& matrix, const char* label) {
	Novice::ScreenPrintf(x, y, "%s", label);
	for (int row = 0; row < 4; ++row) {
		for (int column = 0; column < 4; ++column) {
			Novice::ScreenPrintf(
				x + column * kColumnWidth, y + row * kRowHeight + kRowHeight, "%6.03f", matrix.m[row][column]);
		}
	}
}












// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {


	



	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 500, 720);

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };


	Vector3 axis = geometryUtility.normalize({ 1.0f,1.0f,1.0f });
	float angle = 0.44f;


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
		Matrix4x4 rotateMatrix = MakeRotateAxisAngle(axis, angle);
		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///
		MatrixScreenPrintf(0, 0, rotateMatrix, "rotateMatrix");





		


		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
