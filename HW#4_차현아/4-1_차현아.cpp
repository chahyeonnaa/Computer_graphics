/***********************************************************************/
/*                 HW#4-1 : �κ� ��-�� �𵨸�                          */
/*  �ۼ��� : ������                           ��¥ : 2021�� 10�� 15��  */
/*                                                                     */
/* ���� ���� : �հ��� 3���� ���� Robot Arm ����(�հ��� ���� �ΰ��̻�)  */
/*                                                                     */
/* ��� : <1> ������ ù��° �հ��� �ݺ� ������                         */
/*        <2> ������ �ι�° �հ��� �ݺ� ������                         */
/*        <3> ������ ����° �հ��� �ݺ� ������                         */
/*        <4> ������ ��� �հ��� �ݺ� ������                           */
/*         S ������ �հ��� ������ ����                                 */
/*         * �߰���� *                                                */
/*         <���콺 ���ʹ�ư> ������ ��� ��ó�� ��� ������ ȸ��       */
/*         <���콺 �����ʹ�ư> �����ڼ��� �ǵ��ư�                     */
/***********************************************************************/
#include <stdlib.h>
#include <GL/glut.h>
void Mytimer1(int value); // Ÿ�̸Ӿȿ��� �ݴ���� Ÿ�̸Ӹ� �ҷ����ϹǷ� �Լ���������
void Mytimer4(int value);
void Mytimer6(int value);
int a = 0, b = 0, c = 0; // ȸ������ ������ ���� ���� Ƚ���� ������ִ� ����
int stop = 0; // S�� ������ �� �������� ������Ű�� ���� Ÿ�̸��ݹ�� Ű���� �ݹ��� �������ִ� ����
static int shoulder = 0, elbow = 0, finger1 = 0, finger2 = 0, finger3 = 0; // �� ������ ȸ������

void MyInit(void) {
    glClearColor(0.0, 0.0, 0.0, 1.0); // ������ ������
    glShadeModel(GL_FLAT);
}

void MyDisplay(void) {
    glClear(GL_COLOR_BUFFER_BIT);

    glPushMatrix(); // �ʱ� ���� ����

    glTranslatef(-3.0, 0.0, 0.0); // x������ -3��ŭ ���� �׸���(�հ��� ����, ���ú��� ���)
    glRotatef((GLfloat)shoulder, 0.0, 0.0, 1.0); // shoulder��ŭ ȸ��
    glTranslatef(1.0, 0.0, 0.0); // ��ġ�̵�
    glPushMatrix();	// ���� ��ǥ ����
    glColor3f(1.0, 1.0, 1.0);
    glScalef(2.0, 0.4, 1.0);
    glutWireCube(1.0);
    glPopMatrix();// Ȯ������ �����

    // ������ �׸� ������ǥ���ٰ� �Ȳ�ġ �׸���
    glTranslatef(1.0, 0.0, 0.0);
    glRotatef((GLfloat)elbow, 0.0, 0.0, 1.0); // elbow��ŭ ȸ��
    glTranslatef(1.0, 0.0, 0.0);
    glPushMatrix();	// �Ȳ�ġ ����
    glColor3f(1.0, 1.0, 1.0);
    glScalef(2.0, 0.4, 1.0);
    glutWireCube(1.0);
    glPopMatrix(); // Ȯ������ �����

    // �հ��� �׸���
    glRotatef(20.0, 0.0, 0.0, 1.0); // ��ü������ ���� ���ϱ� ���ؼ� �հ����� �ణ ȸ����Ŵ 
    glPushMatrix(); // 1�� �հ��� ����(1�� �հ��� ��ü�� finger1��ŭ �Ȱ��� ȸ����Ű�� ����)
    // 1-1�� �հ���(�Ȳ�ġ ��Ŀ��ٰ� �׸���)
    glTranslatef(1.2, -0.3, -0.7);
    glRotatef((GLfloat)finger1, 0.0, 0.0, 1.0);
    glTranslatef(0.3, 0.0, 0.0);
    glPushMatrix();// 1-1 �հ��� �������
    glScalef(1.2, 0.3, 0.3);
    glutWireCube(0.6);
    glPopMatrix(); // Ȯ������ �����

    // 1-2 �հ���(������ �׸� 1-1 ��Ŀ��ٰ� �׸���)
    glTranslatef(0.4, 0.0, 0.0);
    glRotatef((GLfloat)finger1, 0.0, 0.0, 1.0);
    glTranslatef(0.4, 0.0, 0.0);
    glPushMatrix(); // 1-2 �հ��� ��� ����
    glScalef(1.2, 0.3, 0.3);
    glutWireCube(0.6);
    glPopMatrix(); // Ȯ������ �����

    // 1-3 �հ���
    glTranslatef(0.4, 0.0, 0.0);
    glRotatef((GLfloat)finger1, 0.0, 0.0, 1.0);
    glTranslatef(0.4, 0.0, 0.0);
    glPushMatrix(); // 1-3 �հ��� ��� ����
    glScalef(1.2, 0.3, 0.3);
    glutWireCube(0.6);
    glPopMatrix(); // Ȯ������ �����

    glPopMatrix(); // 1�� �հ��� ��

    // 2�� �հ���
    glRotatef(-20.0, 0.0, 0.0, 1.0); // ��ü������ ���� ���ϱ� ���� �ణ ȸ��������
    glPushMatrix();  // 2�� �հ��� ����(2�� �հ��� ��ü�� finger2��ŭ �Ȱ��� ȸ����Ű�� ����)
    // 2-1�� �հ���(�Ȳ�ġ ��Ŀ��ٰ� ��ȯ�ؾ���)
    glTranslatef(1.2, 0.0, -0.7);
    glRotatef((GLfloat)finger2, 0.0, 0.0, 1.0);
    glTranslatef(0.4, 0.0, 0.0);
    glPushMatrix();// 2-1 �������
    glScalef(1.2, 0.3, 0.3);
    glutWireCube(0.6);
    glPopMatrix(); // Ȯ������ �����

    // 2-2 �հ���
    glTranslatef(0.4, 0.0, 0.0);
    glRotatef((GLfloat)finger2, 0.0, 0.0, 1.0);
    glTranslatef(0.4, 0.0, 0.0);
    glPushMatrix(); // 2-2 �������
    glScalef(1.2, 0.3, 0.3);
    glutWireCube(0.6);
    glPopMatrix(); // Ȯ������ �����

    // 2-3 �հ���
    glTranslatef(0.4, 0.0, 0.0);
    glRotatef((GLfloat)finger2, 0.0, 0.0, 1.0);
    glTranslatef(0.4, 0.0, 0.0);
    glPushMatrix(); // 2-3 �������
    glScalef(1.2, 0.3, 0.3);
    glutWireCube(0.6);
    glPopMatrix(); // Ȯ������ �����

    glPopMatrix(); // 2�� �հ��� ��


    glRotatef(-21.0, 0.0, 0.0, 1.0);
    glPushMatrix(); // 3�� �հ��� ����(3�� �հ��� ��ü�� finger3��ŭ �Ȱ��� ȸ����Ű�� ����)
    // 3-1�� �հ���(�Ȳ�ġ ��Ŀ��ٰ� ��ȯ�ؾ���)
    glTranslatef(1.2, 0.3, -0.7);
    glRotatef((GLfloat)finger3, 0.0, 0.0, 1.0);
    glTranslatef(0.4, 0.0, 0.0);
    glPushMatrix();// 3-1 �������
    glScalef(1.2, 0.3, 0.3);
    glutWireCube(0.6);
    glPopMatrix(); // Ȯ������ �����

    // 3-2 �հ���
    glTranslatef(0.4, 0.0, 0.0);
    glRotatef((GLfloat)finger3, 0.0, 0.0, 1.0);
    glTranslatef(0.4, 0.0, 0.0);
    glPushMatrix(); // 3-2 �������
    glScalef(1.2, 0.3, 0.3);
    glutWireCube(0.6);
    glPopMatrix(); // Ȯ������ �����

    // 3-3
    glTranslatef(0.4, 0.0, 0.0);
    glRotatef((GLfloat)finger3, 0.0, 0.0, 1.0);
    glTranslatef(0.4, 0.0, 0.0);
    glPushMatrix(); // 3-3 �������
    glScalef(1.2, 0.3, 0.3);
    glutWireCube(0.6);
    glPopMatrix(); // Ȯ������ �����

    glPopMatrix(); // 3�� �հ��� ��

    glPopMatrix(); // �ʱ�������� ���ư���

    glutSwapBuffers();
}
void Mytimer2(int value) // 1���հ����� ��ġ�� �Լ�
{
    a--; // �հ����� �������� ȸ������ ������ ���� ���̴� Ƚ�� ���
         // �����·� ���ư��� �ٽ� ������ �Լ��� ȣ���� �� �ְ�����
    finger1 = (finger1 - 10) % 180;

    if (stop == 1) // S�� �������� Ÿ�̸� ���߱�
        return;

    glutPostRedisplay(); // ���÷��� �ݹ��Լ� ������ ȣ��

    if (a == 0)  // �հ����� �� ����������, �հ����� �����ִ� Mytimer1 �Լ�ȣ��
    {
        glutTimerFunc(100, Mytimer1, 1);
    }
    else
        glutTimerFunc(100, Mytimer2, 1); // �̸� ���ص� limit�� �������� �ʾ����� ��� Mytimer2ȣ��
}
void Mytimer1(int value) // 1�� �������� ȣ��Ǵ� �Լ�
{
    a++; // �հ����� ������ ȸ������ ������ ���� ���̴� Ƚ�� ���

    finger1 = (finger1 + 10) % 180; 

    if (stop == 1) // S�� �������� Ÿ�̸� ���߱�
        return;

    glutPostRedisplay(); // ���÷��� �ݹ��Լ� ������ ȣ��

    if (a >= 8) // �հ����� ������� ��������, �հ����� �����ִ� Mytimer2 �Լ�ȣ��
    {
        glutTimerFunc(100, Mytimer2, 1);
    }
    else
        glutTimerFunc(100, Mytimer1, 1); // �̸� ���ص� limit�� �������� �ʾ����� ��� Mytimer1ȣ��
}
// ��� Ÿ�̸� �Լ��� ������ �����ϹǷ�, ���� Ÿ�̸� �Լ� 2���� �ּ��� �ڼ��ϰ� �ۼ��Ͽ����ϴ�.
void Mytimer3(int value) // 2�� �������� ȣ��Ǵ� �Լ�(�ι�°�հ���)
{
    b++; // �հ����� ������ ȸ������ ������ ���� ���̴� Ƚ�� ���

    finger2 = (finger2 + 10) % 180;

    if (stop == 1) // S�� �������� Ÿ�̸� ���߱�
        return;
    glutPostRedisplay(); // ���÷��� �ݹ��Լ� ������ ȣ��
    if (b >= 8)  // �հ����� ������� ��������, �հ����� �����ִ� Mytimer4 �Լ�ȣ��
    {
        glutTimerFunc(100, Mytimer4, 1);
    }
    else
        glutTimerFunc(100, Mytimer3, 1);
}
void Mytimer4(int value) // �ι�° �հ����� ��ġ���ϴ� �Լ�
{
    b--; // �հ����� �������� ȸ������ ������ ���� ���̴� Ƚ�� ���
         // �����·� ���ư��� �ٽ� ������ �Լ��� ȣ���� �� �ְ�����
    finger2 = (finger2 - 10) % 180;
    if (stop == 1)
        return;
    glutPostRedisplay();
    if (b == 0) // �հ����� �� ����������, �հ����� �����ִ� Mytimer3 �Լ�ȣ��
    {
        glutTimerFunc(100, Mytimer3, 1);
    }
    else
        glutTimerFunc(100, Mytimer4, 1);
}
void Mytimer5(int value) // ����° �հ��� ������ �ϴ� �Լ�
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
void Mytimer6(int value) // ����° �հ��� ��ġ�� �Լ�
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
void MyReshape(int w, int h) { // ������ ũ�Ⱑ ������ ��, �ְ��� �Ͼ�� �ʵ��� ������ ũ�⵵ �������ִ� �Լ�
    glViewport(0, 0, (GLsizei)w, (GLsizei)h); // ������ ������ ��ü�� �������� ����
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(65.0, (GLfloat)w / (GLfloat)h, 1.0, 20.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0, 0.0, -5.0);
}

void MyKeyboard(unsigned char key, int x, int y) { // Ű���� �ݹ� �Լ�
    switch (key) {
    case '1': // 1�̴�������
        glutTimerFunc(100, Mytimer1, 1); // Mytimer1ȣ��
        break;
    case '2': // 2�� ��������
        glutTimerFunc(100, Mytimer3, 1); // Mytimer3ȣ��
        break;
    case '3': // 3�� ��������
        glutTimerFunc(100, Mytimer5, 1); //  Mytimer5ȣ��
        break;
    case '4': // 4�� ��������
        glutTimerFunc(100, Mytimer1, 1); // �հ��� ��ü�� ������ �� �ְ� ��ü Ÿ�̸� ȣ��
        glutTimerFunc(100, Mytimer3, 1);
        glutTimerFunc(100, Mytimer5, 1);
        break;
    case 'S': // S������ ���۱׸�
        stop = 1; // stop���� 1�� ����
        break;
    default:
        break;
    }
    glutPostRedisplay();
}
void MyMouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) // ���� ���콺 Ŭ����
    {
        if (shoulder >= 0.06) // ȸ������ ������ ���� ����� �������� Ư�� ������ �Ѿ�� ������ �ʵ��� �Ͽ���
        {
            return;
        }
        // ��� ������ �����ϰ� ������ ������ ���
        shoulder = (shoulder + 10) % 180; 
        elbow = (elbow + 40) % 180;
        finger1 = (finger1 + 70) % 180;
        finger2 = (finger2 + 60) % 180;
        finger3 = (finger3 + 60) % 180;

    }
    else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) // ������ ��ư Ŭ����
    {
        shoulder = 0; // ��� �������� ���ڸ��� ����
        elbow = 0;
        finger1 = 0;
        finger2 = 0;
        finger3 = 0;
        a = 0; // Ű����� �հ����� �����ϰ� SŰ�� ���� ���� ��,
        b = 0; // ������ ���콺�� Ŭ���ϸ� �ʱ���·� �ǵ��� �� �ֵ��� �Ͽ���
        c = 0; // -> Ű�����ݹ�� ���콺 �ݹ��� ���������
        stop = 0;

    }
}
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600); // ������ ũ��
    glutInitWindowPosition(100, 120); // ������ ��ġ
    glutCreateWindow("Robot Arm");
    MyInit();
    glutDisplayFunc(MyDisplay); // �ݹ��Լ� ���
    glutReshapeFunc(MyReshape);
    glutKeyboardFunc(MyKeyboard);
    glutMouseFunc(MyMouse);
    glutMainLoop();
    return 0;
}