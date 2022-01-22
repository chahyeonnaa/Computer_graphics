/***********************************************************************/
/*                 HW#4-1 : 로봇 손-팔 모델링                          */
/*  작성자 : 차현아                           날짜 : 2021년 10월 15일  */
/*                                                                     */
/* 문제 정의 : 손가락 3개를 가진 Robot Arm 제작(손가락 관절 두개이상)  */
/*                                                                     */
/* 기능 : <1> 누르면 첫번째 손가락 반복 움직임                         */
/*        <2> 누르면 두번째 손가락 반복 움직임                         */
/*        <3> 누르면 세번째 손가락 반복 움직임                         */
/*        <4> 누르면 모든 손가락 반복 움직임                           */
/*         S 누르면 손가락 움직임 정지                                 */
/*         * 추가기능 *                                                */
/*         <마우스 왼쪽버튼> 물건을 잡는 것처럼 모든 관절이 회전       */
/*         <마우스 오른쪽버튼> 원래자세로 되돌아감                     */
/***********************************************************************/
#include <stdlib.h>
#include <GL/glut.h>
void Mytimer1(int value); // 타이머안에서 반대방향 타이머를 불러야하므로 함수원형선언
void Mytimer4(int value);
void Mytimer6(int value);
int a = 0, b = 0, c = 0; // 회전각도 제한을 위해 꺾임 횟수를 기록해주는 변수
int stop = 0; // S를 눌렀을 때 움직임을 정지시키기 위해 타이머콜백과 키보드 콜백을 연결해주는 변수
static int shoulder = 0, elbow = 0, finger1 = 0, finger2 = 0, finger3 = 0; // 각 부위의 회전각도

void MyInit(void) {
    glClearColor(0.0, 0.0, 0.0, 1.0); // 배경색은 검정색
    glShadeModel(GL_FLAT);
}

void MyDisplay(void) {
    glClear(GL_COLOR_BUFFER_BIT);

    glPushMatrix(); // 초기 원점 저장

    glTranslatef(-3.0, 0.0, 0.0); // x축으로 -3만큼 가서 그리기(손가락 길이, 가시부피 고려)
    glRotatef((GLfloat)shoulder, 0.0, 0.0, 1.0); // shoulder만큼 회전
    glTranslatef(1.0, 0.0, 0.0); // 위치이동
    glPushMatrix();	// 윗팔 좌표 저장
    glColor3f(1.0, 1.0, 1.0);
    glScalef(2.0, 0.4, 1.0);
    glutWireCube(1.0);
    glPopMatrix();// 확대흔적 지우기

    // 위에서 그린 윗팔좌표에다가 팔꿈치 그리기
    glTranslatef(1.0, 0.0, 0.0);
    glRotatef((GLfloat)elbow, 0.0, 0.0, 1.0); // elbow만큼 회전
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
    glRotatef((GLfloat)finger1, 0.0, 0.0, 1.0);
    glTranslatef(0.3, 0.0, 0.0);
    glPushMatrix();// 1-1 손가락 행렬저장
    glScalef(1.2, 0.3, 0.3);
    glutWireCube(0.6);
    glPopMatrix(); // 확대흔적 지우기

    // 1-2 손가락(위에서 그린 1-1 행렬에다가 그리기)
    glTranslatef(0.4, 0.0, 0.0);
    glRotatef((GLfloat)finger1, 0.0, 0.0, 1.0);
    glTranslatef(0.4, 0.0, 0.0);
    glPushMatrix(); // 1-2 손가락 행렬 저장
    glScalef(1.2, 0.3, 0.3);
    glutWireCube(0.6);
    glPopMatrix(); // 확대흔적 지우기

    // 1-3 손가락
    glTranslatef(0.4, 0.0, 0.0);
    glRotatef((GLfloat)finger1, 0.0, 0.0, 1.0);
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
    glRotatef((GLfloat)finger2, 0.0, 0.0, 1.0);
    glTranslatef(0.4, 0.0, 0.0);
    glPushMatrix();// 2-1 행렬저장
    glScalef(1.2, 0.3, 0.3);
    glutWireCube(0.6);
    glPopMatrix(); // 확대흔적 지우기

    // 2-2 손가락
    glTranslatef(0.4, 0.0, 0.0);
    glRotatef((GLfloat)finger2, 0.0, 0.0, 1.0);
    glTranslatef(0.4, 0.0, 0.0);
    glPushMatrix(); // 2-2 행렬저장
    glScalef(1.2, 0.3, 0.3);
    glutWireCube(0.6);
    glPopMatrix(); // 확대흔적 지우기

    // 2-3 손가락
    glTranslatef(0.4, 0.0, 0.0);
    glRotatef((GLfloat)finger2, 0.0, 0.0, 1.0);
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
    glRotatef((GLfloat)finger3, 0.0, 0.0, 1.0);
    glTranslatef(0.4, 0.0, 0.0);
    glPushMatrix();// 3-1 행렬저장
    glScalef(1.2, 0.3, 0.3);
    glutWireCube(0.6);
    glPopMatrix(); // 확대흔적 지우기

    // 3-2 손가락
    glTranslatef(0.4, 0.0, 0.0);
    glRotatef((GLfloat)finger3, 0.0, 0.0, 1.0);
    glTranslatef(0.4, 0.0, 0.0);
    glPushMatrix(); // 3-2 행렬저장
    glScalef(1.2, 0.3, 0.3);
    glutWireCube(0.6);
    glPopMatrix(); // 확대흔적 지우기

    // 3-3
    glTranslatef(0.4, 0.0, 0.0);
    glRotatef((GLfloat)finger3, 0.0, 0.0, 1.0);
    glTranslatef(0.4, 0.0, 0.0);
    glPushMatrix(); // 3-3 행렬저장
    glScalef(1.2, 0.3, 0.3);
    glutWireCube(0.6);
    glPopMatrix(); // 확대흔적 지우기

    glPopMatrix(); // 3번 손가락 끝

    glPopMatrix(); // 초기원점으로 돌아가기

    glutSwapBuffers();
}
void Mytimer2(int value) // 1번손가락을 펼치는 함수
{
    a--; // 손가락이 펼쳐지는 회전각도 제한을 위해 꺾이는 횟수 기록
         // 원상태로 돌아가면 다시 접히는 함수를 호출할 수 있게해줌
    finger1 = (finger1 - 10) % 180;

    if (stop == 1) // S가 눌려지면 타이머 멈추기
        return;

    glutPostRedisplay(); // 디스플레이 콜백함수 인위적 호출

    if (a == 0)  // 손가락이 다 펼쳐졌으면, 손가락을 접혀주는 Mytimer1 함수호출
    {
        glutTimerFunc(100, Mytimer1, 1);
    }
    else
        glutTimerFunc(100, Mytimer2, 1); // 미리 정해둔 limit에 도달하지 않았으면 계속 Mytimer2호출
}
void Mytimer1(int value) // 1이 눌려지면 호출되는 함수
{
    a++; // 손가락이 접히는 회전각도 제한을 위해 꺾이는 횟수 기록

    finger1 = (finger1 + 10) % 180; 

    if (stop == 1) // S가 눌려지면 타이머 멈추기
        return;

    glutPostRedisplay(); // 디스플레이 콜백함수 인위적 호출

    if (a >= 8) // 손가락이 어느정도 접혔으면, 손가락을 펼쳐주는 Mytimer2 함수호출
    {
        glutTimerFunc(100, Mytimer2, 1);
    }
    else
        glutTimerFunc(100, Mytimer1, 1); // 미리 정해둔 limit에 도달하지 않았으면 계속 Mytimer1호출
}
// 모든 타이머 함수의 로직은 동일하므로, 위의 타이머 함수 2개의 주석만 자세하게 작성하였습니다.
void Mytimer3(int value) // 2가 눌려지면 호출되는 함수(두번째손가락)
{
    b++; // 손가락이 접히는 회전각도 제한을 위해 꺾이는 횟수 기록

    finger2 = (finger2 + 10) % 180;

    if (stop == 1) // S가 눌려지면 타이머 멈추기
        return;
    glutPostRedisplay(); // 디스플레이 콜백함수 인위적 호출
    if (b >= 8)  // 손가락이 어느정도 접혔으면, 손가락을 펼쳐주는 Mytimer4 함수호출
    {
        glutTimerFunc(100, Mytimer4, 1);
    }
    else
        glutTimerFunc(100, Mytimer3, 1);
}
void Mytimer4(int value) // 두번째 손가락을 펼치게하는 함수
{
    b--; // 손가락이 펼쳐지는 회전각도 제한을 위해 꺾이는 횟수 기록
         // 원상태로 돌아가면 다시 접히는 함수를 호출할 수 있게해줌
    finger2 = (finger2 - 10) % 180;
    if (stop == 1)
        return;
    glutPostRedisplay();
    if (b == 0) // 손가락이 다 펼쳐졌으면, 손가락을 접혀주는 Mytimer3 함수호출
    {
        glutTimerFunc(100, Mytimer3, 1);
    }
    else
        glutTimerFunc(100, Mytimer4, 1);
}
void Mytimer5(int value) // 세번째 손가락 접히게 하는 함수
{
    c++;

    finger3 = (finger3 + 10) % 180;
    if (stop == 1)
        return;
    glutPostRedisplay();
    if (c >= 8)
    {
        glutTimerFunc(100, Mytimer6, 1);
    }
    else
        glutTimerFunc(100, Mytimer5, 1);
}
void Mytimer6(int value) // 세번째 손가락 펼치는 함수
{
    c--;
    finger3 = (finger3 - 10) % 180;
    if (stop == 1)
        return;
    glutPostRedisplay();
    if (c == 0)
    {
        glutTimerFunc(100, Mytimer5, 1);
    }
    else
        glutTimerFunc(100, Mytimer6, 1);
}
void MyReshape(int w, int h) { // 윈도의 크기가 조정될 때, 왜곡이 일어나지 않도록 뷰폿의 크기도 조정해주는 함수
    glViewport(0, 0, (GLsizei)w, (GLsizei)h); // 조정된 윈도우 전체를 뷰폿으로 지정
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(65.0, (GLfloat)w / (GLfloat)h, 1.0, 20.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0, 0.0, -5.0);
}

void MyKeyboard(unsigned char key, int x, int y) { // 키보드 콜백 함수
    switch (key) {
    case '1': // 1이눌려지면
        glutTimerFunc(100, Mytimer1, 1); // Mytimer1호출
        break;
    case '2': // 2가 눌려지면
        glutTimerFunc(100, Mytimer3, 1); // Mytimer3호출
        break;
    case '3': // 3가 눌려지면
        glutTimerFunc(100, Mytimer5, 1); //  Mytimer5호출
        break;
    case '4': // 4가 눌려지면
        glutTimerFunc(100, Mytimer1, 1); // 손가락 전체를 움직일 수 있게 전체 타이머 호출
        glutTimerFunc(100, Mytimer3, 1);
        glutTimerFunc(100, Mytimer5, 1);
        break;
    case 'S': // S누르면 동작그만
        stop = 1; // stop값을 1로 세팅
        break;
    default:
        break;
    }
    glutPostRedisplay();
}
void MyMouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) // 왼쪽 마우스 클릭시
    {
        if (shoulder >= 0.06) // 회전각도 제한을 위해 어깨를 기준으로 특정 각도가 넘어가면 꺾이지 않도록 하였음
        {
            return;
        }
        // 모든 부위를 적절하게 움직여 물건을 잡기
        shoulder = (shoulder + 10) % 180; 
        elbow = (elbow + 40) % 180;
        finger1 = (finger1 + 70) % 180;
        finger2 = (finger2 + 60) % 180;
        finger3 = (finger3 + 60) % 180;

    }
    else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) // 오른쪽 버튼 클릭시
    {
        shoulder = 0; // 모든 관절들을 제자리로 세팅
        elbow = 0;
        finger1 = 0;
        finger2 = 0;
        finger3 = 0;
        a = 0; // 키보드로 손가락을 조작하고 S키를 통해 멈춘 뒤,
        b = 0; // 오른쪽 마우스를 클릭하면 초기상태로 되돌릴 수 있도록 하였음
        c = 0; // -> 키보드콜백과 마우스 콜백을 연결시켜줌
        stop = 0;

    }
}
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600); // 윈도우 크기
    glutInitWindowPosition(100, 120); // 윈도우 위치
    glutCreateWindow("Robot Arm");
    MyInit();
    glutDisplayFunc(MyDisplay); // 콜백함수 등록
    glutReshapeFunc(MyReshape);
    glutKeyboardFunc(MyKeyboard);
    glutMouseFunc(MyMouse);
    glutMainLoop();
    return 0;
}