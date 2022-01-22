/***********************************************************************/
/*                 HW#4-2 : ���� Can Robot �𵨸�                      */
/*  �ۼ��� : ������                           ��¥ : 2021�� 10�� 15��  */
/*                                                                     */
/* ���� ���� : ���� �κ� �𵨸�                                        */
/*                                                                     */
/* ��� : ���� �ڼ��� �ʱ� �⺻�ڼ��� �����Ͽ� �𵨸�                  */
/*        <�޴�>                                                       */
/*        �Ӹ� �����̱�, ������ �����̱�, ������ �����̱�,             */
/*        �����ٸ� �����̱�, ���ʴٸ� �����̱�                         */
/* �޴� Ŭ���� �ش� �޴��� �´� ��ü�� �ѹ� �������ٰ� ���� �ڼ��� ���ƿ� */
/*        S ������ �����̴� ��ü�� ����                                */
/***********************************************************************/
#include <stdlib.h>
#include <GL/glut.h>
// �� �������� ȸ������
static int left_leg = 0, elbow = 0, head = 0, right_arm = 0, left_arm = 0, right_leg = 0;
int a = 0; // ȸ������ ������ ���� �����ϴ� ����
int stop = 0;

void head_MyTimer2(int value) // �Ӹ��� ���ڸ��� ���ƿ��� �ϴ� �Լ�
{
	if (stop == 1) // S�� �������� stop���� 1�� ���õ�
	{
		stop = 0; // stop�� 1�� ���õǸ� �ٸ� ������ �Բ� �������������Ƿ� stop���� �ٽ� 0���� ����������
		return;  // Ÿ�̸� ���߱�

	}

	head = head - 10; // ������ ���� ���ڸ��� ���ƿ�

	glutPostRedisplay(); // ���÷��� �ݹ��Լ� ����ȣ��

}
void head_MyTimer1(int value) // �Ӹ��� �����̰��ϴ� Ÿ�̸�
{
	if (stop == 1) // S�� �������� stop���� 1�� ���õ�
	{
		stop = 0; // stop�� 1�� ���õǸ� �ٸ� ������ �Բ� �������������Ƿ� stop���� �ٽ� 0���� ����������
		return; // Ÿ�̸� ���߱�
	}
	if (a == 1) // �ش� �޴��� �ٽ� ������ ������ �� �ֵ��� 
		a = 0; // a���� �ٽ� 0���� ����

	a++; // ���̴� Ƚ�� ���
	head = head + 10; // 10��ŭ ���̰���(�Ӹ��� �����̴� ��ó�� ���̰� �ϱ� ���� ������ ���� ����)

	glutPostRedisplay(); // ���÷��� �ݹ��Լ� ������ ȣ��

	if (a == 1) // �ѹ� ��������, �ٽ� �����ڼ��� ȸ��
		glutTimerFunc(500, head_MyTimer2, 1); // ���� ���� ���ƿ��� �Լ� �θ���

}
void right_arm_MyTimer2(int value) // �������� ���ڸ��� ���ƿ��� �ϴ� Ÿ�̸�(Ÿ�̸�2�� 2���� ���� ����)
{
	if (stop == 1)
	{
		stop = 0;
		return;
	}
	right_arm = right_arm - 30;

	glutPostRedisplay();

}
void right_arm_MyTimer1(int value) // ������ Ÿ�̸�
{
	if (stop == 1) // S�� �������� stop���� 1�� ���õ�
	{
		stop = 0; // stop�� 1�� ���õǸ� �ٸ� ������ �Բ� �������������Ƿ� stop���� �ٽ� 0���� ����������
		return; // Ÿ�̸� ���߱�
	}
	if (a == 1) // �ش� �޴��� �ٽ� ������ ������ �� �ֵ��� 
		a = 0; // a���� �ٽ� 0���� ����

	a++; // ������ Ƚ�� ���
	right_arm = right_arm + 30;

	glutPostRedisplay();

	if (a == 1) // �ѹ� ���������� ���ڸ��� ���ƿ��� �Լ� ȣ��
		glutTimerFunc(500, right_arm_MyTimer2, 1);

}
void left_arm_MyTimer2(int value) // ������ ���ڸ��� �� �� �ְ� ���ִ� Ÿ�̸�
{
	if (stop == 1)
	{
		stop = 0;
		return;
	}
	left_arm = left_arm + 30;

	glutPostRedisplay();

}
void left_arm_MyTimer1(int value) // ���� Ÿ�̸�
{
	if (stop == 1) // S�� �������� stop���� 1�� ���õ�
	{
		stop = 0; // stop�� 1�� ���õǸ� �ٸ� ������ �Բ� �������������Ƿ� stop���� �ٽ� 0���� ����������
		return; // Ÿ�̸� ���߱�
	}
	if (a == 1) // �ش� �޴��� �ٽ� ������ ������ �� �ֵ��� 
		a = 0; // a���� �ٽ� 0���� ����

	a++; // ������ Ƚ�� ���
	left_arm = left_arm - 30;

	glutPostRedisplay();

	if (a == 1) // ���ڸ��� ���ƿ��� �ϴ� �Լ� ȣ��
		glutTimerFunc(500, left_arm_MyTimer2, 1);

}
void right_leg_MyTimer2(int value) // �����ٸ��� ���ڸ��� �� �� �ְ� �ϴ� Ÿ�̸�
{
	if (stop == 1)
	{
		stop = 0;
		return;
	}
	right_leg = right_leg - 30;

	glutPostRedisplay();

}
void right_leg_MyTimer1(int value) // �����ٸ� Ÿ�̸�
{
	if (stop == 1) // S�� �������� stop���� 1�� ���õ�
	{
		stop = 0; // stop�� 1�� ���õǸ� �ٸ� ������ �Բ� �������������Ƿ� stop���� �ٽ� 0���� ����������
		return; // Ÿ�̸� ���߱�
	}
	if (a == 1) // �ش� �޴��� �ٽ� ������ ������ �� �ֵ��� 
		a = 0; // a���� �ٽ� 0���� ����

	a++;
	right_leg = right_leg + 30;

	glutPostRedisplay();

	if (a == 1) // ���ڸ��� ���ƿ��� �ϴ� �Լ� ȣ��
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
void left_leg_MyTimer1(int value) // �޴ٸ� Ÿ�̸�
{
	if (stop == 1) // S�� �������� stop���� 1�� ���õ�
	{
		stop = 0; // stop�� 1�� ���õǸ� �ٸ� ������ �Բ� �������������Ƿ� stop���� �ٽ� 0���� ����������
		return; // Ÿ�̸� ���߱�
	}
	if (a == 1) // �ش� �޴��� �ٽ� ������ ������ �� �ֵ��� 
		a = 0; // a���� �ٽ� 0���� ����

	a++;
	left_leg = left_leg - 30;

	glutPostRedisplay();

	if (a == 1)
		glutTimerFunc(500, left_leg_MyTimer2, 1);

}
void MyMainMenu(int entryID) { // �޴��Լ�
	if (entryID == 1)      glutTimerFunc(500, head_MyTimer1, 1); // ù��° �׸��� ��������, �Ӹ��� �����̰��ϴ� Ÿ�̸� ����
	if (entryID == 2)      glutTimerFunc(500, right_arm_MyTimer1, 1); // �ι�° �׸��� ��������, �������� �����̰��ϴ� Ÿ�̸� ����
	if (entryID == 3)      glutTimerFunc(500, left_arm_MyTimer1, 1); // ����° �׸��� ��������, ������ �����̰��ϴ� Ÿ�̸� ����
	if (entryID == 4)      glutTimerFunc(500, right_leg_MyTimer1, 1); // �׹�° �׸��� ��������, �����ٸ��� �����̰��ϴ� Ÿ�̸� ����
	if (entryID == 5)      glutTimerFunc(500, left_leg_MyTimer1, 1); // �ټ���° �׸��� ��������, �޴ٸ��� �����̰��ϴ� Ÿ�̸� ����

	glutPostRedisplay(); // ���������� ���÷��� �ݹ��Լ��� �ҷ��ֱ�
}

void MyInit(void) {
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glShadeModel(GL_FLAT);

	GLint MyMainMenuID = glutCreateMenu(MyMainMenu); // �޴� ����
	glutAddMenuEntry("Moving Head", 1); // �޴��׸� ÷��
	glutAddMenuEntry("Moving Right arm", 2); // ���ڴ� �׸��� ���õɶ� �޴��ݹ� �Լ����� ���޵Ǵ� ������
	glutAddMenuEntry("Moving Left arm", 3);
	glutAddMenuEntry("Moving Right legs", 4);
	glutAddMenuEntry("Moving Left legs", 5);
	glutAttachMenu(GLUT_RIGHT_BUTTON); // ���콺 ������ ��ư Ŭ���� �޴��� ����
}

void MyDisplay(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLineWidth(2); // ���� �β��� �������� ����

	glPushMatrix(); // ���� ����

	glTranslatef(0.0, -1.0, 0.0); // ����׸���
	glTranslatef(0.0, 1.0, 0.0);
	glPushMatrix(); // ��������
	glColor3f(0.0, 0.5, 1.0);
	glScalef(1.4, 1.7, 1.4);
	glutWireCube(1.0);
	glPopMatrix(); // Ȯ�� ���� �����

	// ���뿡�ٰ� ��׸���
	glTranslatef(-1.0, 0.9, 0.0);
	glTranslatef(1.0, 0.12, 0.3);
	glPushMatrix();	// ������
	glColor3f(1.0, 1.0, 1.0);
	glScalef(0.5, 0.4, 1.4);
	glutWireCube(1.0);
	glPopMatrix(); // Ȯ������ �����

	// �񿡴ٰ� �Ӹ� �׸���
	glTranslatef(0.0, 0.57, 0.0);
	glRotatef((GLfloat)head, 0.0, 0.0, 1.0); // head��ŭ �Ӹ� ȸ��
	glTranslatef(0.0, 0.1, 0.0);
	glPushMatrix(); // �Ӹ� ��� ����
	glColor3f(1.0, 1.0, 1.0);
	glScalef(1.3, 0.9, 1.4);
	glutWireCube(1.0);
	glPopMatrix(); // Ȯ������ �����
	glPopMatrix(); // �Ӹ�����

	// �������� ���ƿͼ� �� �׸���
	glPushMatrix(); // �ٽ� ���� �������ֱ�

	glTranslatef(0.7, 0.88, 0.0);
	glRotatef((GLfloat)right_arm, 0.0, 0.0, 1.0);
	glTranslatef(0.2, -0.45, 0.0);
	glPushMatrix(); // ������ 1�� ����
	glScalef(0.4, 0.8, 1.4);
	glColor3f(0.5, 0.6, 0.8);
	glutWireCube(1.0);
	glPopMatrix(); // Ȯ������ �����

	// ������ 1�����ٰ� �̾ 2�� �׸���
	glTranslatef(0.0, -0.2, 0.0);
	glTranslatef(0.0, -0.6, 0.0);
	glPushMatrix(); // ������ 2�� ����
	glScalef(0.4, 0.8, 1.4);
	glColor3f(0.6, 0.7, 0.9);
	glutSolidCube(1.0);
	glPopMatrix(); // Ȯ������ �����
	glPopMatrix(); // ������ ����

	//�������� ���ƿͼ� ������ �׸���
	glPushMatrix(); // �ٽ� ���� �����Ű��

	glTranslatef(-0.7, 0.88, 0.0);
	glRotatef((GLfloat)left_arm, 0.0, 0.0, 1.0);
	glTranslatef(-0.2, -0.45, 0.0);
	glPushMatrix(); // ���� 1�� ����
	glColor3f(0.3, 0.4, 0.6);
	glScalef(0.4, 0.8, 1.4);
	glutWireCube(1.0);
	glPopMatrix(); // Ȯ�� ���� �����

	// ���� 2��
	glTranslatef(0.0, -0.2, 0.0);
	glTranslatef(0.0, -0.6, 0.0);
	glPushMatrix(); // ���� 2�� ����
	glScalef(0.4, 0.8, 1.4);
	glColor3f(0.3, 0.4, 0.6);
	glutSolidCube(1.0);
	glPopMatrix(); // Ȯ������ �����
	glPopMatrix(); // ���� ����

	// �������� ���ƿͼ� �ٸ������
	glPushMatrix(); // �ٽ� ���� ����
	glTranslatef(-0.6, -0.85, 0.0);
	glRotatef((GLfloat)left_leg, 0.0, 0.0, 1.0);
	glTranslatef(+0.2, -0.2, 0.0);
	glPushMatrix(); // 1�� �޴ٸ� ����
	glScalef(0.3, 0.4, 1.4);
	glColor3f(0.3, 0.4, 0.6);
	glutSolidCube(1.0);
	glPopMatrix(); // Ȯ������ �����

	// 2�� �޴ٸ�
	glTranslatef(0.0, -0.2, 0.0);
	glTranslatef(0.0, -0.2, 0.0);
	glPushMatrix(); // �޴ٸ� 2 ����
	glScalef(0.3, 0.4, 1.4);
	glColor3f(0.3, 0.4, 0.6);
	glutSolidCube(1.0);
	glPopMatrix(); // Ȯ������ �����

	glPopMatrix(); // �޴ٸ� ����

	// �������� ���ƿͼ� �����ٸ� �׸���
	glPushMatrix(); // �ٽ� ���� ����
	glTranslatef(0.6, -0.85, 0.0);
	glRotatef((GLfloat)right_leg, 0.0, 0.0, 1.0);
	glTranslatef(-0.2, -0.2, 0.0);
	glPushMatrix(); // �����ٸ� 1 ����
	glScalef(0.3, 0.4, 1.4);
	glColor3f(0.6, 0.7, 0.9);
	glutSolidCube(1.0);
	glPopMatrix(); // Ȯ������ �����

	// �����ٸ� 2 �׸���
	glTranslatef(0.0, -0.2, 0.0);
	glTranslatef(0.0, -0.2, 0.0);
	glPushMatrix(); // �����ٸ� 2 ����
	glScalef(0.3, 0.4, 1.4);
	glColor3f(0.6, 0.7, 0.9);
	glutSolidCube(1.0);
	glPopMatrix(); // Ȯ������ �����
	glPopMatrix(); // �����ٸ� ���� -> ������ ����Ǿ�����

	glPopMatrix(); // ������ �� �����
	glutSwapBuffers();
}

void MyReshape(int w, int h) { // ������ ũ�Ⱑ ����������, ������ ũ�⵵ �Բ� �������� �ְ��� �����ִ� �Լ�
	glViewport(0, 0, (GLsizei)w, (GLsizei)h); // ���Ӱ� ������ �������� ũ�⸦ �������� ����
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(65.0, (GLfloat)w / (GLfloat)h, 1.0, 20.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0, 0.0, -5.0);
}

void MyKeyboard(unsigned char key, int x, int y) { // Ű���� �ݹ��Լ�
	switch (key) {
	case 'S': // S�� ��������, stop���� 1�� �����Ͽ� Ÿ�̸Ӹ� ���� �������� ���� �� �ְ��Ͽ���
		stop = 1;
		break;

	default:
		break;
	}
	glutPostRedisplay(); // ���÷��� �ݹ��Լ� ���������� �ҷ��ֱ�
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Robot Arm");
	MyInit();
	glutDisplayFunc(MyDisplay); // �ݹ��Լ� ���
	glutReshapeFunc(MyReshape);
	glutKeyboardFunc(MyKeyboard);
	glutMainLoop();
	return 0;
}

