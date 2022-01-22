/***********************************************************************/
/*                 HW#4-2 : 전신 Can Robot 모델링                      */
/*  작성자 : 차현아                           날짜 : 2021년 10월 15일  */
/*                                                                     */
/* 문제 정의 : 깡통 로봇 모델링                                        */
/*                                                                     */
/* 기능 : 차렷 자세를 초기 기본자세로 설정하여 모델링                  */
/*        <메뉴>                                                       */
/*        머리 움직이기, 오른팔 움직이기, 왼쪽팔 움직이기,             */
/*        오른다리 움직이기, 왼쪽다리 움직이기                         */
/* 메뉴 클릭시 해당 메뉴에 맞는 신체가 한번 움직였다가 원래 자세로 돌아옴 */
/*        S 누르면 움직이는 신체가 멈춤                                */
/***********************************************************************/
#include <stdlib.h>
#include <GL/glut.h>
// 각 관절들의 회전각도
static int left_leg = 0, elbow = 0, head = 0, right_arm = 0, left_arm = 0, right_leg = 0;
int a = 0; // 회전각도 제한을 위해 존재하는 변수
int stop = 0;

void head_MyTimer2(int value) // 머리를 제자리로 돌아오게 하는 함수
{
	if (stop == 1) // S가 눌려지면 stop값이 1로 세팅됨
	{
		stop = 0; // stop이 1로 세팅되면 다른 부위도 함께 동작하지않으므로 stop값을 다시 0으로 만들어줘야함
		return;  // 타이머 멈추기

	}

	head = head - 10; // 꺾였던 고개가 제자리로 돌아옴

	glutPostRedisplay(); // 디스플레이 콜백함수 인위호출

}
void head_MyTimer1(int value) // 머리를 움직이게하는 타이머
{
	if (stop == 1) // S가 눌려지면 stop값이 1로 세팅됨
	{
		stop = 0; // stop이 1로 세팅되면 다른 부위도 함께 동작하지않으므로 stop값을 다시 0으로 만들어줘야함
		return; // 타이머 멈추기
	}
	if (a == 1) // 해당 메뉴를 다시 눌러도 움직일 수 있도록 
		a = 0; // a값을 다시 0으로 세팅

	a++; // 꺾이는 횟수 기록
	head = head + 10; // 10만큼 꺾이게함(머리를 움직이는 것처럼 보이게 하기 위해 적절히 각도 조정)

	glutPostRedisplay(); // 디스플레이 콜백함수 인위적 호출

	if (a == 1) // 한번 꺾였으면, 다시 원래자세로 회복
		glutTimerFunc(500, head_MyTimer2, 1); // 원래 고개로 돌아오는 함수 부르기

}
void right_arm_MyTimer2(int value) // 오른팔을 제자리로 돌아오게 하는 타이머(타이머2는 2끼리 로직 동일)
{
	if (stop == 1)
	{
		stop = 0;
		return;
	}
	right_arm = right_arm - 30;

	glutPostRedisplay();

}
void right_arm_MyTimer1(int value) // 오른팔 타이머
{
	if (stop == 1) // S가 눌려지면 stop값이 1로 세팅됨
	{
		stop = 0; // stop이 1로 세팅되면 다른 부위도 함께 동작하지않으므로 stop값을 다시 0으로 만들어줘야함
		return; // 타이머 멈추기
	}
	if (a == 1) // 해당 메뉴를 다시 눌러도 움직일 수 있도록 
		a = 0; // a값을 다시 0으로 세팅

	a++; // 움직임 횟수 기록
	right_arm = right_arm + 30;

	glutPostRedisplay();

	if (a == 1) // 한번 움직였으면 제자리로 돌아오는 함수 호출
		glutTimerFunc(500, right_arm_MyTimer2, 1);

}
void left_arm_MyTimer2(int value) // 왼팔을 제자리로 올 수 있게 해주는 타이머
{
	if (stop == 1)
	{
		stop = 0;
		return;
	}
	left_arm = left_arm + 30;

	glutPostRedisplay();

}
void left_arm_MyTimer1(int value) // 왼팔 타이머
{
	if (stop == 1) // S가 눌려지면 stop값이 1로 세팅됨
	{
		stop = 0; // stop이 1로 세팅되면 다른 부위도 함께 동작하지않으므로 stop값을 다시 0으로 만들어줘야함
		return; // 타이머 멈추기
	}
	if (a == 1) // 해당 메뉴를 다시 눌러도 움직일 수 있도록 
		a = 0; // a값을 다시 0으로 세팅

	a++; // 움직임 횟수 기록
	left_arm = left_arm - 30;

	glutPostRedisplay();

	if (a == 1) // 제자리로 돌아오게 하는 함수 호출
		glutTimerFunc(500, left_arm_MyTimer2, 1);

}
void right_leg_MyTimer2(int value) // 오른다리를 제자리로 올 수 있게 하는 타이머
{
	if (stop == 1)
	{
		stop = 0;
		return;
	}
	right_leg = right_leg - 30;

	glutPostRedisplay();

}
void right_leg_MyTimer1(int value) // 오른다리 타이머
{
	if (stop == 1) // S가 눌려지면 stop값이 1로 세팅됨
	{
		stop = 0; // stop이 1로 세팅되면 다른 부위도 함께 동작하지않으므로 stop값을 다시 0으로 만들어줘야함
		return; // 타이머 멈추기
	}
	if (a == 1) // 해당 메뉴를 다시 눌러도 움직일 수 있도록 
		a = 0; // a값을 다시 0으로 세팅

	a++;
	right_leg = right_leg + 30;

	glutPostRedisplay();

	if (a == 1) // 제자리로 돌아오게 하는 함수 호출
		glutTimerFunc(500, right_leg_MyTimer2, 1);

}void left_leg_MyTimer2(int value)
{
	if (stop == 1)
	{
		stop = 0;
		return;
	}
	left_leg = left_leg + 30;

	glutPostRedisplay();

}
void left_leg_MyTimer1(int value) // 왼다리 타이머
{
	if (stop == 1) // S가 눌려지면 stop값이 1로 세팅됨
	{
		stop = 0; // stop이 1로 세팅되면 다른 부위도 함께 동작하지않으므로 stop값을 다시 0으로 만들어줘야함
		return; // 타이머 멈추기
	}
	if (a == 1) // 해당 메뉴를 다시 눌러도 움직일 수 있도록 
		a = 0; // a값을 다시 0으로 세팅

	a++;
	left_leg = left_leg - 30;

	glutPostRedisplay();

	if (a == 1)
		glutTimerFunc(500, left_leg_MyTimer2, 1);

}
void MyMainMenu(int entryID) { // 메뉴함수
	if (entryID == 1)      glutTimerFunc(500, head_MyTimer1, 1); // 첫번째 항목이 눌려지면, 머리를 움직이게하는 타이머 동작
	if (entryID == 2)      glutTimerFunc(500, right_arm_MyTimer1, 1); // 두번째 항목이 눌려지면, 오른팔을 움직이게하는 타이머 동작
	if (entryID == 3)      glutTimerFunc(500, left_arm_MyTimer1, 1); // 세번째 항목이 눌려지면, 왼팔을 움직이게하는 타이머 동작
	if (entryID == 4)      glutTimerFunc(500, right_leg_MyTimer1, 1); // 네번째 항목이 눌려지면, 오른다리를 움직이게하는 타이머 동작
	if (entryID == 5)      glutTimerFunc(500, left_leg_MyTimer1, 1); // 다섯번째 항목이 눌려지면, 왼다리를 움직이게하는 타이머 동작

	glutPostRedisplay(); // 인위적으로 디스플레이 콜백함수를 불러주기
}

void MyInit(void) {
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glShadeModel(GL_FLAT);

	GLint MyMainMenuID = glutCreateMenu(MyMainMenu); // 메뉴 생성
	glutAddMenuEntry("Moving Head", 1); // 메뉴항목 첨가
	glutAddMenuEntry("Moving Right arm", 2); // 숫자는 항목이 선택될때 메뉴콜백 함수에게 전달되는 정수값
	glutAddMenuEntry("Moving Left arm", 3);
	glutAddMenuEntry("Moving Right legs", 4);
	glutAddMenuEntry("Moving Left legs", 5);
	glutAttachMenu(GLUT_RIGHT_BUTTON); // 마우스 오른쪽 버튼 클릭시 메뉴가 보임
}

void MyDisplay(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLineWidth(2); // 선의 두께는 보기좋게 조정

	glPushMatrix(); // 원점 저장

	glTranslatef(0.0, -1.0, 0.0); // 몸통그리기
	glTranslatef(0.0, 1.0, 0.0);
	glPushMatrix(); // 몸통저장
	glColor3f(0.0, 0.5, 1.0);
	glScalef(1.4, 1.7, 1.4);
	glutWireCube(1.0);
	glPopMatrix(); // 확대 흔적 지우기

	// 몸통에다가 목그리기
	glTranslatef(-1.0, 0.9, 0.0);
	glTranslatef(1.0, 0.12, 0.3);
	glPushMatrix();	// 목저장
	glColor3f(1.0, 1.0, 1.0);
	glScalef(0.5, 0.4, 1.4);
	glutWireCube(1.0);
	glPopMatrix(); // 확대흔적 지우기

	// 목에다가 머리 그리기
	glTranslatef(0.0, 0.57, 0.0);
	glRotatef((GLfloat)head, 0.0, 0.0, 1.0); // head만큼 머리 회전
	glTranslatef(0.0, 0.1, 0.0);
	glPushMatrix(); // 머리 행렬 저장
	glColor3f(1.0, 1.0, 1.0);
	glScalef(1.3, 0.9, 1.4);
	glutWireCube(1.0);
	glPopMatrix(); // 확대흔적 지우기
	glPopMatrix(); // 머리빼기

	// 몸통으로 돌아와서 팔 그리기
	glPushMatrix(); // 다시 원점 저장해주기

	glTranslatef(0.7, 0.88, 0.0);
	glRotatef((GLfloat)right_arm, 0.0, 0.0, 1.0);
	glTranslatef(0.2, -0.45, 0.0);
	glPushMatrix(); // 오른팔 1번 저장
	glScalef(0.4, 0.8, 1.4);
	glColor3f(0.5, 0.6, 0.8);
	glutWireCube(1.0);
	glPopMatrix(); // 확대흔적 지우기

	// 오른팔 1번에다가 이어서 2번 그리기
	glTranslatef(0.0, -0.2, 0.0);
	glTranslatef(0.0, -0.6, 0.0);
	glPushMatrix(); // 오른팔 2번 저장
	glScalef(0.4, 0.8, 1.4);
	glColor3f(0.6, 0.7, 0.9);
	glutSolidCube(1.0);
	glPopMatrix(); // 확대흔적 지우기
	glPopMatrix(); // 오른팔 빼기

	//몸통으로 돌아와서 왼쪽팔 그리기
	glPushMatrix(); // 다시 원점 저장시키기

	glTranslatef(-0.7, 0.88, 0.0);
	glRotatef((GLfloat)left_arm, 0.0, 0.0, 1.0);
	glTranslatef(-0.2, -0.45, 0.0);
	glPushMatrix(); // 왼팔 1번 저장
	glColor3f(0.3, 0.4, 0.6);
	glScalef(0.4, 0.8, 1.4);
	glutWireCube(1.0);
	glPopMatrix(); // 확대 흔적 지우기

	// 왼팔 2번
	glTranslatef(0.0, -0.2, 0.0);
	glTranslatef(0.0, -0.6, 0.0);
	glPushMatrix(); // 왼팔 2번 저장
	glScalef(0.4, 0.8, 1.4);
	glColor3f(0.3, 0.4, 0.6);
	glutSolidCube(1.0);
	glPopMatrix(); // 확대흔적 지우기
	glPopMatrix(); // 왼팔 빼기

	// 몸통으로 돌아와서 다리만들기
	glPushMatrix(); // 다시 원점 저장
	glTranslatef(-0.6, -0.85, 0.0);
	glRotatef((GLfloat)left_leg, 0.0, 0.0, 1.0);
	glTranslatef(+0.2, -0.2, 0.0);
	glPushMatrix(); // 1번 왼다리 저장
	glScalef(0.3, 0.4, 1.4);
	glColor3f(0.3, 0.4, 0.6);
	glutSolidCube(1.0);
	glPopMatrix(); // 확대흔적 지우기

	// 2번 왼다리
	glTranslatef(0.0, -0.2, 0.0);
	glTranslatef(0.0, -0.2, 0.0);
	glPushMatrix(); // 왼다리 2 저장
	glScalef(0.3, 0.4, 1.4);
	glColor3f(0.3, 0.4, 0.6);
	glutSolidCube(1.0);
	glPopMatrix(); // 확대흔적 지우기

	glPopMatrix(); // 왼다리 삭제

	// 몸통으로 돌아와서 오른다리 그리기
	glPushMatrix(); // 다시 원점 저장
	glTranslatef(0.6, -0.85, 0.0);
	glRotatef((GLfloat)right_leg, 0.0, 0.0, 1.0);
	glTranslatef(-0.2, -0.2, 0.0);
	glPushMatrix(); // 오른다리 1 저장
	glScalef(0.3, 0.4, 1.4);
	glColor3f(0.6, 0.7, 0.9);
	glutSolidCube(1.0);
	glPopMatrix(); // 확대흔적 지우기

	// 오른다리 2 그리기
	glTranslatef(0.0, -0.2, 0.0);
	glTranslatef(0.0, -0.2, 0.0);
	glPushMatrix(); // 오른다리 2 저장
	glScalef(0.3, 0.4, 1.4);
	glColor3f(0.6, 0.7, 0.9);
	glutSolidCube(1.0);
	glPopMatrix(); // 확대흔적 지우기
	glPopMatrix(); // 오른다리 빼기 -> 원점만 저장되어있음

	glPopMatrix(); // 스택이 다 비워짐
	glutSwapBuffers();
}

void MyReshape(int w, int h) { // 윈도우 크기가 조정됐을때, 뷰폿의 크기도 함께 조절시켜 왜곡을 막아주는 함수
	glViewport(0, 0, (GLsizei)w, (GLsizei)h); // 새롭게 조정된 윈도우의 크기를 뷰폿으로 지정
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(65.0, (GLfloat)w / (GLfloat)h, 1.0, 20.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0, 0.0, -5.0);
}

void MyKeyboard(unsigned char key, int x, int y) { // 키보드 콜백함수
	switch (key) {
	case 'S': // S가 눌려지면, stop값을 1로 세팅하여 타이머를 멈춰 움직임을 멈출 수 있게하였음
		stop = 1;
		break;

	default:
		break;
	}
	glutPostRedisplay(); // 디스플레이 콜백함수 인위적으로 불러주기
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Robot Arm");
	MyInit();
	glutDisplayFunc(MyDisplay); // 콜백함수 등록
	glutReshapeFunc(MyReshape);
	glutKeyboardFunc(MyKeyboard);
	glutMainLoop();
	return 0;
}

