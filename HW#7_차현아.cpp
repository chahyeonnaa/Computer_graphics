/***********************************************************************/
/*                 HW#7 : ���� ����                                    */
/*  �ۼ��� : ������                           ��¥ : 2021�� 11�� 12��  */
/*                                                                     */
/* ���� ���� : ����ĵ�κ� ����                                         */
/*                                                                     */
/* ��� : ����ĵ�κ��� ������ ������, �ٴ� ��� �����ϱ�               */
/*        <R �Ǵ� rŰ�� ������, ���Ȱ� ��ٸ��� �����ϰ� �������� �޸��� ����� �ǰ���*/
/*         0�� ������ �κ��� ���߰� ������, ������ ��ü���� Ư���� �����Ͽ��� */
/*         �κ��� ������ ������ �����ӿ����� ������ ������ ����        */
/***********************************************************************/
#include <GL/glut.h>
#include <stdlib.h>

// �� �������� ȸ������
static int left_leg = 0, left_leg2 = 0, head = 0, right_arm = 0;
static int left_arm = 0, right_arm2 = 0, right_leg = 0, right_leg2 = 0, body = 0, left_arm2 = 0;
int a = 0; // ȸ������ ������ ���� �����ϴ� ����

void right_arm_MyTimer1(int value);
void left_arm_MyTimer1(int value);
void right_leg_MyTimer1(int value);
void left_leg_MyTimer1(int value);
void head_MyTimer1(int value);
void body_MyTimer1(int value);

void InitLight() {
	// ������ ��
	GLfloat light0_ambient[] = { 0.5, 0.4, 0.3, 1.0 }; // �ֺ��ݻ籤
	GLfloat light0_diffuse[] = { 0.8, 0.5, 0.6, 1.0 }; // ���ݻ籤
	GLfloat light0_specular[] = { 1.0, 1.0, 1.0, 1.0 }; // ���ݻ籤

	glEnable(GL_DEPTH_TEST); // opengl �ý����� ��������� �������� ����� �ϵ��� ����
	glEnable(GL_LIGHTING);//���� ��� Ȱ��ȭ
	glEnable(GL_LIGHT0);// 0�� ���� �ѱ�
	glLightfv(GL_LIGHT0, GL_AMBIENT, light0_ambient); // 0�� �������� ������ ���� �� ����
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light0_specular);
}
void body_MyTimer2(int value) // ���� ���ڸ��� ���ƿ��� �ϴ� �Լ�
{
	body = body - 10; // ���� ���ڸ��� ���ƿ�

	glutTimerFunc(200, body_MyTimer1, 1);
	glutPostRedisplay();

}
void body_MyTimer1(int value) // ���� �����̰��ϴ� Ÿ�̸�
{

	if (a == 1) 
		a = 0; // a���� �ٽ� 0���� ����

	a++; // ���̴� Ƚ�� ���
	body = body + 10; // 10��ŭ ���̰���(���� �����̴� ��ó�� ���̰� �ϱ� ���� ������ ���� ����)

	glutPostRedisplay(); // ���÷��� �ݹ��Լ� ������ ȣ��

	if (a == 1) // �ѹ� ��������, �ٽ� �����ڼ��� ȸ��
		glutTimerFunc(200, body_MyTimer2, 1); // ���� ��ġ�� ���ƿ��� �Լ� �θ���

}
void head_MyTimer2(int value) // �Ӹ��� ���ڸ��� ���ƿ��� �ϴ� �Լ�
{
	head = head - 10; // ������ ���� ���ڸ��� ���ƿ�

	glutTimerFunc(200, head_MyTimer1, 1);
	glutPostRedisplay();


}
void head_MyTimer1(int value) // �Ӹ��� �����̰��ϴ� Ÿ�̸�
{
	if (a == 1) 
		a = 0; // a���� �ٽ� 0���� ����

	a++; // ���̴� Ƚ�� ���
	head = head + 10; // 10��ŭ ���̰���(�Ӹ��� �����̴� ��ó�� ���̰� �ϱ� ���� ������ ���� ����)

	glutPostRedisplay(); // ���÷��� �ݹ��Լ� ������ ȣ��

	if (a == 1) // �ѹ� ��������, �ٽ� �����ڼ��� ȸ��
		glutTimerFunc(200, head_MyTimer2, 1); // ���� ���� ���ƿ��� �Լ� �θ���

}
void right_arm_MyTimer2(int value) // �������� ���ڸ��� ���ƿ��� �ϴ� Ÿ�̸�(Ÿ�̸�2�� 2���� ���� ����)
{

	right_arm = right_arm - 30;
	right_arm2 = right_arm2 + 10;

	glutTimerFunc(200, right_arm_MyTimer1, 1);
	glutPostRedisplay();

}
void right_arm_MyTimer1(int value) // ������ Ÿ�̸�
{

	if (a == 1) 
		a = 0; // a���� �ٽ� 0���� ����

	a++; // ������ Ƚ�� ���
	right_arm = -340; // �������� ���� ������ ����
	right_arm2 = right_arm2 - 10; // �ι�° ������ ������ ����

	glutPostRedisplay();

	if (a == 1) // �ѹ� ���������� ���ڸ��� ���ƿ��� �Լ� ȣ��
		glutTimerFunc(200, right_arm_MyTimer2, 1);

}
void left_arm_MyTimer2(int value) // ������ ���ڸ��� �� �� �ְ� ���ִ� Ÿ�̸�
{
	left_arm = -340; // ������ ������ ����(�������� ���ڸ��� ���ƿ�)
	left_arm2 = left_arm2 - 25;
	glutTimerFunc(200, left_arm_MyTimer1, 1);
	glutPostRedisplay();

}
void left_arm_MyTimer1(int value) // ���� Ÿ�̸�
{

	if (a == 1) 
		a = 0; // a���� �ٽ� 0���� ����

	a++; // ������ Ƚ�� ���
	left_arm = 0; // �������� ���� �����Ƿ�, ������ ���� ������ �ֱ�
	left_arm2 = left_arm2 + 25;
	glutPostRedisplay();

	if (a == 1) // ���ڸ��� ���ƿ��� �ϴ� �Լ� ȣ��
		glutTimerFunc(200, left_arm_MyTimer2, 1);

}
void right_leg_MyTimer2(int value) // �����ٸ��� ���ڸ��� �� �� �ְ� �ϴ� Ÿ�̸�
{
	right_leg = right_leg + 30;
	right_leg2 = 0;

	glutTimerFunc(200, right_leg_MyTimer1, 1);

	glutPostRedisplay();

}
void right_leg_MyTimer1(int value) // �����ٸ� Ÿ�̸�
{
	if (a == 1)  
		a = 0; // a���� �ٽ� 0���� ����

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
void left_leg_MyTimer1(int value) // �޴ٸ� Ÿ�̸�
{
	if (a == 1) 
		a = 0; // a���� �ٽ� 0���� ����

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
	glShadeModel(GL_FLAT); // �����������_�÷����̵�
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient); // ���������_ ��繰ü�鿡 ���� �̾��� ���� �߰�
}

void MyDisplay(void) {
	// ��ü���� Ư�� ����
	GLfloat mat_ambient[] = { 0.4, 0.4, 0.8, 1.0 }; // �ֺ��ݻ翡 ���� ��ü��
	GLfloat mat_diffuse[] = { 0.7, 0.5, 0.8, 1.0 }; // ���ݻ翡 ���� ��ü��
	GLfloat mat_specular[] = { 0.0, 0.0, 0.0, 1.0 }; // ���ݻ翡 ���� ��ü��
	GLfloat mat_emission[] = { 0.3, 0.2, 0.2, 0.0 };

	GLfloat LightPosition[] = { 0.0, 2.0, 4.0, 2.0 }; // ��ġ��(��)����

	// �׸��� �׸������� ������ �ʱ�ȭ, ���̹��� �ʱ�ȭ(�������Ÿ� ����)
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLineWidth(2); // ���� �β��� �������� ����

	glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 0.8); // �Ÿ��� ���� �� ����ȿ��_ ���Ǽ��� ��ȭ
	glLightfv(GL_LIGHT0, GL_POSITION, LightPosition); //������ġ����_������ ������ǥ�迡 ��ġ��Ŵ

	glPushMatrix(); // ���� ����

	glTranslatef(0.0, -1.0, 0.0); // ����׸���
	glRotatef((GLfloat)body, 0.0, (GLfloat)body, 1.0); // head��ŭ �Ӹ� ȸ��
	glTranslatef(0.0, 1.0, 0.0);
	glPushMatrix(); // ��������
	glColor3f(0.0, 0.5, 1.0);
	glScalef(1.4, 1.7, 1.4);
	// ��ü�� Ư�� ����_�ո�
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient); // �ֺ������_�ֺ��ݻ翡 ���� ��ü��
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse); // ���ݻ籤���_���ݻ翡 ���� ��ü��
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular); // ���ݻ籤���_���ݻ翡 ���� ��ü��
	glutWireCube(1.0);
	glPopMatrix(); // Ȯ�� ���� �����

	// ���뿡�ٰ� ��׸���
	glTranslatef(-1.0, 0.9, 0.0);
	glTranslatef(1.0, 0.12, 0.3);
	glPushMatrix();	// ������
	glColor3f(1.0, 1.0, 1.0);
	glScalef(0.5, 0.4, 1.4);
	// ��ü�� Ư�� ����_�ո�
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient); // �ֺ������_�ֺ��ݻ翡 ���� ��ü��
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse); // ���ݻ籤���_���ݻ翡 ���� ��ü��
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular); // ���ݻ籤���_���ݻ翡 ���� ��ü��
	glutSolidCube(1.0);
	glPopMatrix(); // Ȯ������ �����

	// �񿡴ٰ� �Ӹ� �׸���
	glTranslatef(0.0, 0.57, 0.0);
	glRotatef((GLfloat)head, (GLfloat)head, 0.0, 1.0); // head��ŭ �Ӹ� ȸ��
	glTranslatef(0.0, 0.1, 0.0);
	glPushMatrix(); // �Ӹ� ��� ����
	glColor3f(1.0, 1.0, 1.0);
	glScalef(1.3, 0.9, 1.4);
	// ��ü�� Ư�� ����_�ո�
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient); // �ֺ������_�ֺ��ݻ翡 ���� ��ü��
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse); // ���ݻ籤���_���ݻ翡 ���� ��ü��
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular); // ���ݻ籤���_���ݻ翡 ���� ��ü��
	//glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
	glutSolidCube(1.0);
	glPopMatrix(); // Ȯ������ �����
	glPopMatrix(); // �Ӹ�����

	// �������� ���ƿͼ� �� �׸���
	glPushMatrix(); // �ٽ� ���� �������ֱ�

	glTranslatef(0.7, 0.88, 0.0);
	glRotatef((GLfloat)right_arm, (GLfloat)right_arm, 0.0, 1.0);
	glTranslatef(0.2, -0.45, 0.0);
	glPushMatrix(); // ������ 1�� ����
	glScalef(0.4, 0.8, 1.4);
	glColor3f(0.5, 0.6, 0.8);
	glutWireCube(1.0);
	glPopMatrix(); // Ȯ������ �����

	// ������ 1�����ٰ� �̾ 2�� �׸���
	glTranslatef(0.0, -0.2, 0.0);
	glRotatef((GLfloat)right_arm2, 0.0, (GLfloat)right_arm2, 0.0);
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
	glRotatef((GLfloat)left_arm, (GLfloat)left_arm, 0.0, 0.0);
	glTranslatef(-0.2, -0.45, 0.0);
	glPushMatrix(); // ���� 1�� ����
	glColor3f(0.3, 0.4, 0.6);
	glScalef(0.4, 0.8, 1.4);
	glutWireCube(1.0);
	glPopMatrix(); // Ȯ�� ���� �����

	// ���� 2��
	glTranslatef(0.0, -0.2, 0.0);
	glRotatef((GLfloat)left_arm2, 0.0, (GLfloat)left_arm2, 0.0);
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
	glRotatef((GLfloat)left_leg, (GLfloat)left_leg, 0.0, 1.0);
	glTranslatef(+0.2, -0.2, 0.0);
	glPushMatrix(); // 1�� �޴ٸ� ����
	glScalef(0.3, 0.4, 1.4);
	glColor3f(0.3, 0.4, 0.6);
	glutSolidCube(1.0);
	glPopMatrix(); // Ȯ������ �����

	// 2�� �޴ٸ�
	glTranslatef(0.0, -0.2, 0.0);
	//glRotatef((GLfloat)left_leg, 0.0, 0.0, 1.0);
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
	glRotatef((GLfloat)right_leg, (GLfloat)right_leg, 0.0, 1.0);
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
	case 'R': // R,r�� ������, �κ��� �޸�
	case 'r': // ��, �Ӹ�, �����ȴٸ�, ���ȴٸ��� ������
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
	glutPostRedisplay(); // ���÷��� �ݹ��Լ� ���������� �ҷ��ֱ�
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	// �ִϸ��̼� ȿ���� ���� ���߹��� ���, �����۴� �⺻, �������Ÿ� ���� Z���� ����غ�
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Running Robot");
	InitLight();
	MyInit();
	glutDisplayFunc(MyDisplay); // �ݹ��Լ� ���
	glutReshapeFunc(MyReshape);
	glutKeyboardFunc(MyKeyboard);
	glutMainLoop();
	return 0;
}
