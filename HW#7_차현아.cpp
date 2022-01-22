/***********************************************************************/
/*                 HW#7 : 조명 종합                                    */
/*  작성자 : 차현아                           날짜 : 2021년 11월 12일  */
/*                                                                     */
/* 문제 정의 : 전신캔로봇 수정                                         */
/*                                                                     */
/* 기능 : 전신캔로봇에 조명을 입히고, 뛰는 모습 구현하기               */
/*        <R 또는 r키를 누르면, 양팔과 양다리를 적절하게 움직여서 달리는 모습이 되게함*/
/*         0번 광원이 로봇을 비추고 있으며, 광원과 물체면의 특성을 설정하였음 */
/*         로봇에 조명을 입혀서 움직임에따라 광원에 영향을 받음        */
/***********************************************************************/
#include <GL/glut.h>
#include <stdlib.h>

// 각 관절들의 회전각도
static int left_leg = 0, left_leg2 = 0, head = 0, right_arm = 0;
static int left_arm = 0, right_arm2 = 0, right_leg = 0, right_leg2 = 0, body = 0, left_arm2 = 0;
int a = 0; // 회전각도 제한을 위해 존재하는 변수

void right_arm_MyTimer1(int value);
void left_arm_MyTimer1(int value);
void right_leg_MyTimer1(int value);
void left_leg_MyTimer1(int value);
void head_MyTimer1(int value);
void body_MyTimer1(int value);

void InitLight() {
	// 광원의 색
	GLfloat light0_ambient[] = { 0.5, 0.4, 0.3, 1.0 }; // 주변반사광
	GLfloat light0_diffuse[] = { 0.8, 0.5, 0.6, 1.0 }; // 난반사광
	GLfloat light0_specular[] = { 1.0, 1.0, 1.0, 1.0 }; // 정반사광

	glEnable(GL_DEPTH_TEST); // opengl 시스템이 명시적으로 은면제거 계산을 하도록 설정
	glEnable(GL_LIGHTING);//조명 기능 활성화
	glEnable(GL_LIGHT0);// 0번 광원 켜기
	glLightfv(GL_LIGHT0, GL_AMBIENT, light0_ambient); // 0번 광원에서 나오는 빛의 색 설정
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light0_specular);
}
void body_MyTimer2(int value) // 몸을 제자리로 돌아오게 하는 함수
{
	body = body - 10; // 몸이 제자리로 돌아옴

	glutTimerFunc(200, body_MyTimer1, 1);
	glutPostRedisplay();

}
void body_MyTimer1(int value) // 몸을 움직이게하는 타이머
{

	if (a == 1) 
		a = 0; // a값을 다시 0으로 세팅

	a++; // 꺾이는 횟수 기록
	body = body + 10; // 10만큼 꺾이게함(몸을 움직이는 것처럼 보이게 하기 위해 적절히 각도 조정)

	glutPostRedisplay(); // 디스플레이 콜백함수 인위적 호출

	if (a == 1) // 한번 꺾였으면, 다시 원래자세로 회복
		glutTimerFunc(200, body_MyTimer2, 1); // 원래 위치로 돌아오는 함수 부르기

}
void head_MyTimer2(int value) // 머리를 제자리로 돌아오게 하는 함수
{
	head = head - 10; // 꺾였던 고개가 제자리로 돌아옴

	glutTimerFunc(200, head_MyTimer1, 1);
	glutPostRedisplay();


}
void head_MyTimer1(int value) // 머리를 움직이게하는 타이머
{
	if (a == 1) 
		a = 0; // a값을 다시 0으로 세팅

	a++; // 꺾이는 횟수 기록
	head = head + 10; // 10만큼 꺾이게함(머리를 움직이는 것처럼 보이게 하기 위해 적절히 각도 조정)

	glutPostRedisplay(); // 디스플레이 콜백함수 인위적 호출

	if (a == 1) // 한번 꺾였으면, 다시 원래자세로 회복
		glutTimerFunc(200, head_MyTimer2, 1); // 원래 고개로 돌아오는 함수 부르기

}
void right_arm_MyTimer2(int value) // 오른팔을 제자리로 돌아오게 하는 타이머(타이머2는 2끼리 로직 동일)
{

	right_arm = right_arm - 30;
	right_arm2 = right_arm2 + 10;

	glutTimerFunc(200, right_arm_MyTimer1, 1);
	glutPostRedisplay();

}
void right_arm_MyTimer1(int value) // 오른팔 타이머
{

	if (a == 1) 
		a = 0; // a값을 다시 0으로 세팅

	a++; // 움직임 횟수 기록
	right_arm = -340; // 오른팔이 먼저 앞으로 나감
	right_arm2 = right_arm2 - 10; // 두번째 관절은 적절히 조정

	glutPostRedisplay();

	if (a == 1) // 한번 움직였으면 제자리로 돌아오는 함수 호출
		glutTimerFunc(200, right_arm_MyTimer2, 1);

}
void left_arm_MyTimer2(int value) // 왼팔을 제자리로 올 수 있게 해주는 타이머
{
	left_arm = -340; // 왼팔이 앞으로 나감(오른팔은 제자리로 돌아옴)
	left_arm2 = left_arm2 - 25;
	glutTimerFunc(200, left_arm_MyTimer1, 1);
	glutPostRedisplay();

}
void left_arm_MyTimer1(int value) // 왼팔 타이머
{

	if (a == 1) 
		a = 0; // a값을 다시 0으로 세팅

	a++; // 움직임 횟수 기록
	left_arm = 0; // 오른팔이 먼저 나가므로, 왼팔은 먼저 가만히 있기
	left_arm2 = left_arm2 + 25;
	glutPostRedisplay();

	if (a == 1) // 제자리로 돌아오게 하는 함수 호출
		glutTimerFunc(200, left_arm_MyTimer2, 1);

}
void right_leg_MyTimer2(int value) // 오른다리를 제자리로 올 수 있게 하는 타이머
{
	right_leg = right_leg + 30;
	right_leg2 = 0;

	glutTimerFunc(200, right_leg_MyTimer1, 1);

	glutPostRedisplay();

}
void right_leg_MyTimer1(int value) // 오른다리 타이머
{
	if (a == 1)  
		a = 0; // a값을 다시 0으로 세팅

	a++;
	right_leg = 0;
	right_leg2 = right_leg2 - 10;
	glutPostRedisplay();

	if (a == 1)
		glutTimerFunc(200, right_leg_MyTimer2, 1);

}
void left_leg_MyTimer2(int value)
{

	left_leg = left_leg + 30;
	left_leg2 = left_leg2 - 10;
	glutTimerFunc(200, left_leg_MyTimer1, 1);

	glutPostRedisplay();

}
void left_leg_MyTimer1(int value) // 왼다리 타이머
{
	if (a == 1) 
		a = 0; // a값을 다시 0으로 세팅

	a++;
	left_leg = left_leg - 30;
	left_leg2 = left_leg2 + 10;
	glutPostRedisplay();

	if (a == 1)
		glutTimerFunc(200, left_leg_MyTimer2, 1);

}

void MyInit(void) {
	GLfloat lmodel_ambient[] = { 0.7, 0.7, 0.7, 1.0 };
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glShadeModel(GL_FLAT); // 음영모드정의_플랫쉐이딩
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient); // 전역조명모델_ 모든물체면에 대해 미약한 광원 추가
}

void MyDisplay(void) {
	// 물체면의 특성 정의
	GLfloat mat_ambient[] = { 0.4, 0.4, 0.8, 1.0 }; // 주변반사에 대한 물체색
	GLfloat mat_diffuse[] = { 0.7, 0.5, 0.8, 1.0 }; // 난반사에 대한 물체색
	GLfloat mat_specular[] = { 0.0, 0.0, 0.0, 1.0 }; // 정반사에 대한 물체색
	GLfloat mat_emission[] = { 0.3, 0.2, 0.2, 0.0 };

	GLfloat LightPosition[] = { 0.0, 2.0, 4.0, 2.0 }; // 위치성(점)광원

	// 그림을 그릴때마다 색버퍼 초기화, 깊이버퍼 초기화(은면제거를 위함)
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLineWidth(2); // 선의 두께는 보기좋게 조정

	glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 0.8); // 거리에 따른 빛 감쇠효과_ 빛의세기 변화
	glLightfv(GL_LIGHT0, GL_POSITION, LightPosition); //광원위치설정_광원을 세상좌표계에 위치시킴

	glPushMatrix(); // 원점 저장

	glTranslatef(0.0, -1.0, 0.0); // 몸통그리기
	glRotatef((GLfloat)body, 0.0, (GLfloat)body, 1.0); // head만큼 머리 회전
	glTranslatef(0.0, 1.0, 0.0);
	glPushMatrix(); // 몸통저장
	glColor3f(0.0, 0.5, 1.0);
	glScalef(1.4, 1.7, 1.4);
	// 물체면 특성 정의_앞면
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient); // 주변광계수_주변반사에 대한 물체색
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse); // 난반사광계수_난반사에 대한 물체색
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular); // 정반사광계수_정반사에 대한 물체색
	glutWireCube(1.0);
	glPopMatrix(); // 확대 흔적 지우기

	// 몸통에다가 목그리기
	glTranslatef(-1.0, 0.9, 0.0);
	glTranslatef(1.0, 0.12, 0.3);
	glPushMatrix();	// 목저장
	glColor3f(1.0, 1.0, 1.0);
	glScalef(0.5, 0.4, 1.4);
	// 물체면 특성 정의_앞면
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient); // 주변광계수_주변반사에 대한 물체색
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse); // 난반사광계수_난반사에 대한 물체색
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular); // 정반사광계수_정반사에 대한 물체색
	glutSolidCube(1.0);
	glPopMatrix(); // 확대흔적 지우기

	// 목에다가 머리 그리기
	glTranslatef(0.0, 0.57, 0.0);
	glRotatef((GLfloat)head, (GLfloat)head, 0.0, 1.0); // head만큼 머리 회전
	glTranslatef(0.0, 0.1, 0.0);
	glPushMatrix(); // 머리 행렬 저장
	glColor3f(1.0, 1.0, 1.0);
	glScalef(1.3, 0.9, 1.4);
	// 물체면 특성 정의_앞면
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient); // 주변광계수_주변반사에 대한 물체색
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse); // 난반사광계수_난반사에 대한 물체색
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular); // 정반사광계수_정반사에 대한 물체색
	//glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
	glutSolidCube(1.0);
	glPopMatrix(); // 확대흔적 지우기
	glPopMatrix(); // 머리빼기

	// 몸통으로 돌아와서 팔 그리기
	glPushMatrix(); // 다시 원점 저장해주기

	glTranslatef(0.7, 0.88, 0.0);
	glRotatef((GLfloat)right_arm, (GLfloat)right_arm, 0.0, 1.0);
	glTranslatef(0.2, -0.45, 0.0);
	glPushMatrix(); // 오른팔 1번 저장
	glScalef(0.4, 0.8, 1.4);
	glColor3f(0.5, 0.6, 0.8);
	glutWireCube(1.0);
	glPopMatrix(); // 확대흔적 지우기

	// 오른팔 1번에다가 이어서 2번 그리기
	glTranslatef(0.0, -0.2, 0.0);
	glRotatef((GLfloat)right_arm2, 0.0, (GLfloat)right_arm2, 0.0);
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
	glRotatef((GLfloat)left_arm, (GLfloat)left_arm, 0.0, 0.0);
	glTranslatef(-0.2, -0.45, 0.0);
	glPushMatrix(); // 왼팔 1번 저장
	glColor3f(0.3, 0.4, 0.6);
	glScalef(0.4, 0.8, 1.4);
	glutWireCube(1.0);
	glPopMatrix(); // 확대 흔적 지우기

	// 왼팔 2번
	glTranslatef(0.0, -0.2, 0.0);
	glRotatef((GLfloat)left_arm2, 0.0, (GLfloat)left_arm2, 0.0);
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
	glRotatef((GLfloat)left_leg, (GLfloat)left_leg, 0.0, 1.0);
	glTranslatef(+0.2, -0.2, 0.0);
	glPushMatrix(); // 1번 왼다리 저장
	glScalef(0.3, 0.4, 1.4);
	glColor3f(0.3, 0.4, 0.6);
	glutSolidCube(1.0);
	glPopMatrix(); // 확대흔적 지우기

	// 2번 왼다리
	glTranslatef(0.0, -0.2, 0.0);
	//glRotatef((GLfloat)left_leg, 0.0, 0.0, 1.0);
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
	glRotatef((GLfloat)right_leg, (GLfloat)right_leg, 0.0, 1.0);
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
	case 'R': // R,r을 누르면, 로봇이 달림
	case 'r': // 몸, 머리, 오른팔다리, 왼팔다리가 움직임
		glutTimerFunc(200, body_MyTimer1, 1);
		glutTimerFunc(200, head_MyTimer1, 1);
		glutTimerFunc(200, right_arm_MyTimer1, 1);
		glutTimerFunc(200, left_arm_MyTimer1, 1);
		glutTimerFunc(200, right_leg_MyTimer1, 1);
		glutTimerFunc(200, left_leg_MyTimer1, 1);
		break;
	default:
		break;
	}
	glutPostRedisplay(); // 디스플레이 콜백함수 인위적으로 불러주기
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	// 애니메이션 효과를 위해 이중버퍼 사용, 색버퍼는 기본, 은면제거를 위해 Z버퍼 사용준비
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Running Robot");
	InitLight();
	MyInit();
	glutDisplayFunc(MyDisplay); // 콜백함수 등록
	glutReshapeFunc(MyReshape);
	glutKeyboardFunc(MyKeyboard);
	glutMainLoop();
	return 0;
}
