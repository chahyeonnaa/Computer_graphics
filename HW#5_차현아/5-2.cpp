/***********************************************************************/
/*                 HW#5-2 : 모델뷰변환 종합                            */
/*  작성자 : 차현아                           날짜 : 2021년 10월 29일  */
/*                                                                     */
/* 문제 정의 : 로봇손을 다양한 시점에서 관찰하기                       */
/*                                                                     */
/* 기능 : 양옆방향 제어는 "오직 오른쪽 방향키"로만 조작하도록 설계하였음 */
/*        오른쪽 방향키를 누르면, 360도 회전함                         */
/*        정해진 각도만큼 돌고나면, 제자리로 돌아오도록 설계되어있음   */
/*        위아래 방향키를 통해 위아래 방향조작                         */
/*        오른쪽 방향키, 위아래 방향키를 이용해 모든 방향에서 관찰이 가능함 */
/*        왼쪽 방향키는 사용하지않습니다                                */
/***********************************************************************/
#include <stdlib.h>
#include <GL/glut.h>
float X = 0; // 카메라의 X축좌표 조절
float Y = 0; // 카메라의 Y축좌표 조절
float Z = 0; // 카메라의 Z축좌표 조절
float FocusX = 0; // 초점의 X축좌표 조절
float FocusY = 0; // 초점의 Y축좌표 조절
float FocusZ = 0; // 초점의 Z축좌표 조절
int num = 0; // 방향키가 눌린 횟수에 따라 gluLookAt함수의 좌표 제어
void MyInit(void) {
    glClearColor(0.0, 0.0, 0.0, 1.0); // 배경색은 검정색
    glShadeModel(GL_FLAT);
}

void MyDisplay(void) {
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW); // 모델뷰 행렬을 glLoadIdentity()로 초기화 하지 않으면, 
    glLoadIdentity(); // gluLookAt에서 값들이 쌓이므로 반드시 항등행렬로 초기화 해야함.

    // 뷰행렬이 만들어짐
    // 키를 조작함에따라 카메라위치, 초점이 움직임
    gluLookAt(X, Y, Z, FocusX, FocusY, -50.0 + FocusZ, 0.0, 1.0, 0.0); // 시점변환함수(카메라위치, 초점, 카메라 기울임)

    glPushMatrix(); // 초기 원점 저장

    glTranslatef(-3.0, 0.0, 0.0); // x축으로 -3만큼 가서 그리기(손가락 길이, 가시부피 고려)
    glTranslatef(1.0, 0.0, 0.0); // 위치이동
    glPushMatrix();	// 윗팔 좌표 저장
    glColor3f(1.0, 1.0, 1.0);
    glScalef(2.0, 0.4, 1.0);
    glutWireCube(1.0);
    glPopMatrix();// 확대흔적 지우기

    // 위에서 그린 윗팔좌표에다가 팔꿈치 그리기
    glTranslatef(1.0, 0.0, 0.0);
    glTranslatef(1.0, 0.0, 0.0);
    glPushMatrix();	// 팔꿈치 저장
    glColor3f(1.0, 1.0, 1.0);
    glScalef(2.0, 0.4, 1.0);
    glutWireCube(1.0);
    glPopMatrix(); // 확대흔적 지우기

    // 손가락 그리기
    glRotatef(20.0, 0.0, 0.0, 1.0); // 입체적으로 보기 편하기 위해서 손가락을 약간 회전시킴 
    glPushMatrix(); // 1번 손가락 저장(1번 손가락 전체를 finger1만큼 똑같이 회전시키기 위함)
    // 1-1번 손가락(팔꿈치 행렬에다가 그리기)
    glTranslatef(1.2, -0.3, -0.7);
    glTranslatef(0.3, 0.0, 0.0);
    glPushMatrix();// 1-1 손가락 행렬저장
    glScalef(1.2, 0.3, 0.3);
    glutWireCube(0.6);
    glPopMatrix(); // 확대흔적 지우기

    // 1-2 손가락(위에서 그린 1-1 행렬에다가 그리기)
    glTranslatef(0.4, 0.0, 0.0);
    glTranslatef(0.4, 0.0, 0.0);
    glPushMatrix(); // 1-2 손가락 행렬 저장
    glScalef(1.2, 0.3, 0.3);
    glutWireCube(0.6);
    glPopMatrix(); // 확대흔적 지우기

    // 1-3 손가락
    glTranslatef(0.4, 0.0, 0.0);
    glTranslatef(0.4, 0.0, 0.0);
    glPushMatrix(); // 1-3 손가락 행렬 저장
    glScalef(1.2, 0.3, 0.3);
    glutWireCube(0.6);
    glPopMatrix(); // 확대흔적 지우기

    glPopMatrix(); // 1번 손가락 끝

    // 2번 손가락
    glRotatef(-20.0, 0.0, 0.0, 1.0); // 입체적으로 보기 편하기 위해 약간 회전시켰음
    glPushMatrix();  // 2번 손가락 저장(2번 손가락 전체를 finger2만큼 똑같이 회전시키기 위함)
    // 2-1번 손가락(팔꿈치 행렬에다가 변환해야함)
    glTranslatef(1.2, 0.0, -0.7);
    glTranslatef(0.4, 0.0, 0.0);
    glPushMatrix();// 2-1 행렬저장
    glScalef(1.2, 0.3, 0.3);
    glutWireCube(0.6);
    glPopMatrix(); // 확대흔적 지우기

    // 2-2 손가락
    glTranslatef(0.4, 0.0, 0.0);
    glTranslatef(0.4, 0.0, 0.0);
    glPushMatrix(); // 2-2 행렬저장
    glScalef(1.2, 0.3, 0.3);
    glutWireCube(0.6);
    glPopMatrix(); // 확대흔적 지우기

    // 2-3 손가락
    glTranslatef(0.4, 0.0, 0.0);
    glTranslatef(0.4, 0.0, 0.0);
    glPushMatrix(); // 2-3 행렬저장
    glScalef(1.2, 0.3, 0.3);
    glutWireCube(0.6);
    glPopMatrix(); // 확대흔적 지우기

    glPopMatrix(); // 2번 손가락 끝


    glRotatef(-21.0, 0.0, 0.0, 1.0);
    glPushMatrix(); // 3번 손가락 저장(3번 손가락 전체를 finger3만큼 똑같이 회전시키기 위함)
    // 3-1번 손가락(팔꿈치 행렬에다가 변환해야함)
    glTranslatef(1.2, 0.3, -0.7);
    glTranslatef(0.4, 0.0, 0.0);
    glPushMatrix();// 3-1 행렬저장
    glScalef(1.2, 0.3, 0.3);
    glutWireCube(0.6);
    glPopMatrix(); // 확대흔적 지우기

    // 3-2 손가락
    glTranslatef(0.4, 0.0, 0.0);
    glTranslatef(0.4, 0.0, 0.0);
    glPushMatrix(); // 3-2 행렬저장
    glScalef(1.2, 0.3, 0.3);
    glutWireCube(0.6);
    glPopMatrix(); // 확대흔적 지우기

    // 3-3
    glTranslatef(0.4, 0.0, 0.0);
    glTranslatef(0.4, 0.0, 0.0);
    glPushMatrix(); // 3-3 행렬저장
    glScalef(1.2, 0.3, 0.3);
    glutWireCube(0.6);
    glPopMatrix(); // 확대흔적 지우기

    glPopMatrix(); // 3번 손가락 끝

    glPopMatrix(); // 초기원점으로 돌아가기

    glutSwapBuffers();
}

void MyReshape(int w, int h) { // 윈도의 크기가 조정될 때, 왜곡이 일어나지 않도록 뷰폿의 크기도 조정해주는 함수
    glViewport(0, 0, (GLsizei)w, (GLsizei)h); // 조정된 윈도우 전체를 뷰폿으로 지정
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(65.0, (GLfloat)w / (GLfloat)h, 1.0, 20.0);
    glTranslatef(0.0, 0.0, -5.0);
}
// 모든 방향에서 로봇팔을 볼 수 있도록 카메라위치, 초점의 좌표를 방향마다 적절히 조정하였음
void MySpecial(int key, int x, int y) {

    switch (key) {
    // 옆방향은 카메라의 X,Z좌표, 초점의 X,Z좌표로만 조절
    case GLUT_KEY_RIGHT: // 오른쪽키만으로 양옆방향을 제어함
        if (num >= 26 && num <= 60) // 동북 회전(뒷쪽방향으로 돌리기)
        {
            X = X - 0.06;
            FocusX = FocusX + 2.0;
            FocusZ = FocusZ + 2.0;
        }
        else if (num >= 60 && num <= 74) // 북서(팔의 뒷부분)
        {
            X = X - 0.05;
            FocusX = FocusX + 2.0;
            FocusZ = FocusZ - 0.05;
        }
        else if (num >= 75 && num <= 95) // 북서(팔의 뒷부분)
        {
            X = X - 0.05;
            FocusX = FocusX + 2.0;
            FocusZ = FocusZ + 0.05;
            Z = Z + 0.02;
        }
        else if (num >= 96 && num<=110) // (손가락의 반대 관절부분)완벽한 서쪽을 위한 회전
        {
            X = X - 0.04;
            FocusX = FocusX + 2.5;
            FocusZ = FocusZ + 0.5;
            Z = Z + 0.01;
        }
        else if (num >= 110) // (관절에서 앞쪽으로)남서쪽 회전
        {
            X = X + 0.05;
            FocusX = FocusX + 2.5;
            FocusZ = FocusZ - 3.5;
            Z = Z + 0.005;
        }
        else // 가장 처음_ (num=0일때)동쪽(손가락)까지 회전
        {
            X = X + 0.06;
            FocusX = FocusX - 2.0;
            FocusZ = FocusZ + 3.0;
        }

        if (num >= 166) //160도 회전 후, 모든 좌표들을 제자리로 돌려놓기
        {
            X = 0;
            Y = 0;
            Z = 0;
            FocusX = 0;
            FocusY = 0;
            FocusZ = 0;
            num = 0;
        }
        num++; // 방향키 눌린 횟수 기록
        break;
    case GLUT_KEY_UP: // 윗방향 보기
        Y = Y + 0.01;
        FocusY = FocusY - 3.0;
        break;
    case GLUT_KEY_DOWN: // 아랫방향 보기
        Y = Y - 0.01;
        FocusY = FocusY + 3.0;
        break;
    default:
        break;
    }

    glutPostRedisplay(); // 디스플레이콜백함수 인위적 호출
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Comprehensive Transformation");
    MyInit();
    glutDisplayFunc(MyDisplay); // 콜백함수 등록
    glutReshapeFunc(MyReshape);
    glutSpecialFunc(MySpecial);
    glutMainLoop();
    return 0;
}