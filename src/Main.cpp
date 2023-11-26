// �ȉ��̍s���Ȃ��ƃR���p�C�����ʂ�܂���
#pragma comment(linker, "/subsystem:windows")

//## ���ɉ����Đݒ�
using namespace std; // std���O��Ԃ��g�p
#include "DxLib.h"   // DX���C�u����
#include "Vector.h"  // �x�N�g���N���X
#include "Circle.h"  // �~�N���X
#include "Utils.h"   // ���[�e�B���e�B (��`�̃^��)
#include "Option.h"  // ���̑��ݒ�

// �v���O�����̍ŏ���WinMain�Ŏn�߂�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    //##### �����ݒ� #####//
    ChangeWindowMode(TRUE); // �E�B���h�E���[�h�ݒ�
    SetGraphMode(WIDTH, HEIGHT, 32); // ��ʃT�C�Y�ݒ�
    SetWaitVSyncFlag(TRUE); // ����������L���ɂ���

    float wireAngle = 0.0F; // �\���������Ȃ��Ƃ����Ȃ��炵��

    // DX���C�u��������������
    if(DxLib_Init() == -1) {
        return -1; // �G���[���N�����璼���ɏI��
    }

    // �~�̏�����
    CircleManager circle[2] {
        CircleManager(Vector2(200, HEIGHT / 1.2), 25),
        CircleManager(Vector2(WIDTH / 2, HEIGHT / 1.2), 50)
        //CircleManager(Vector2(WIDTH - 200, HEIGHT / 1.2), 50)
    };

    //##### ���C�����[�v�i�`�揈���j #####//
    while(ProcessMessage() == 0) {
        ClearDrawScreen(); // ��ʂ̍X�V

        printfDx("Hello World!");

        // �����삵�Ă���~�̉ߋ����W�Ɍ��ݍ��W����������
        circle[circleState].posPrevious = circle[circleState].posNow;

        // �L�[�ɓ��͂�����Έړ�����
        // Left or A
        if(CheckHitKey(KEY_INPUT_LEFT) || CheckHitKey(KEY_INPUT_A)) {
            circle[circleState].posNow.x -= 5;
        }
        // Right or D
        if(CheckHitKey(KEY_INPUT_RIGHT) || CheckHitKey(KEY_INPUT_D)) {
            circle[circleState].posNow.x += 5;
        }

        // �~�̕`��ƈړ��E�v�Z�ȂǂȂ�
        for(int i = 0; i < COUNTOF(circle); i++) {
            // �����삵�Ă���~�ɐF�X���
            if(circleState == i) {
                // ���΍��W�����o��
                circle[i].distance = getVectorDistanceSign(circle[i].posNow, circle[i].posPrevious);

                // �p���x�����o��
                circle[i].angularVelocity = PI * circle[i].distance / (circle[i].R() * PI);

                // �ݐϊp�x�Ɋp���x�����Z����
                circle[i].cumulativeAngle += circle[i].angularVelocity;

                //
                circle[i].posVectorEnd = circle[i].posNow;
            }

            // �~�̒��ɐ���`�悷���
            for (int j = 0; j < 2 * COUNTOF(circle); j++) {
                // �������ɕ`�悵�����̂ŕ␳����
                circle[i].posNow.y -= circle[i].R();

                // ���[���W
                circle[i].posVectorEnd.x = circle[i].posNow.X() + (sin(circle[i].cumulativeAngle + wireAngle) * circle[i].R());
                circle[i].posVectorEnd.y = circle[i].posNow.Y() + (cos(circle[i].cumulativeAngle + wireAngle) * circle[i].R());

                // �\�����̕`��
                DrawLine(circle[i].posNow.X(), circle[i].posNow.Y(), circle[i].posVectorEnd.X(), circle[i].posVectorEnd.Y(), white);

                // �␳���Čv�Z�����̂Ō��ɖ߂�
                circle[i].posNow.y += circle[i].R();

                // ���[�𒆉����W��
                circle[i].posVectorEnd = circle[i].posNow;

                // �p�x�̍X�V
                wireAngle += 1.57F;
            }

            // �p�x�̏�����
            wireAngle = 0.0F;
        }

        // �ڐG���܂������H
        for(int i = 0; i < COUNTOF(circle); i++) {
            // �������Ă����瑱�s
            if(circleState == i) continue;
            // �ڐG������
            if(hitCheck(circle[i].posNow, circle[i].R(), circle[!i].posNow, circle[!i].R())) {
                // �����삵�Ă���~��ύX���� 0, 1, 2 ... �ƑΉ��ł���悤�ɂ���B
                circleState = i;
                //circleState = !circleState;

                // �����삵�Ă���~�̐F��ύX����
                circle[i].hit = true;
                break;
            }
            else {
                // �����삵�Ă���~�̐F��ύX����
                circle[i].hit = false;
            }
        }

        // �`�悵�܂��傤
        for(int i = 0; i < COUNTOF(circle); i++) {
            // �ڐG���Ă���~�̐F��ύX����
            if(circle[i].hit)
                DrawCircle(circle[i].posNow.X(), circle[i].posNow.Y() - circle[i].R(), circle[i].R(), red, FALSE);
            else
                DrawCircle(circle[i].posNow.X(), circle[i].posNow.Y() - circle[i].R(), circle[i].R(), white, FALSE);
        }

        // ���
        DrawLine(0, HEIGHT / 1.2, WIDTH, HEIGHT / 1.2, white);

        //Sleep(10); // �x��������

        // ��ʂ̍X�V�i�K�{�j
        ScreenFlip(); // ��ʂ𔽓]�����鏈��
        clsDx();      // �f�o�b�O���O��ʂ��N���A���鏈��
    }

    DxLib_End(); // DX Library�̎g�p���I�����鏈��
    return 0;    // �\�t�g�𐳏�I��
}