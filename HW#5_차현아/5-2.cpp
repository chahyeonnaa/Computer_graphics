/***********************************************************************/
/*                 HW#5-2 : �𵨺亯ȯ ����                            */
/*  �ۼ��� : ������                           ��¥ : 2021�� 10�� 29��  */
/*                                                                     */
/* ���� ���� : �κ����� �پ��� �������� �����ϱ�                       */
/*                                                                     */
/* ��� : �翷���� ����� "���� ������ ����Ű"�θ� �����ϵ��� �����Ͽ��� */
/*        ������ ����Ű�� ������, 360�� ȸ����                         */
/*        ������ ������ŭ ������, ���ڸ��� ���ƿ����� ����Ǿ�����   */
/*        ���Ʒ� ����Ű�� ���� ���Ʒ� ��������                         */
/*        ������ ����Ű, ���Ʒ� ����Ű�� �̿��� ��� ���⿡�� ������ ������ */
/*        ���� ����Ű�� ��������ʽ��ϴ�                                */
/***********************************************************************/
#include <stdlib.h>
#include <GL/glut.h>
float X = 0; // ī�޶��� X����ǥ ����
float Y = 0; // ī�޶��� Y����ǥ ����
float Z = 0; // ī�޶��� Z����ǥ ����
float FocusX = 0; // ������ X����ǥ ����
float FocusY = 0; // ������ Y����ǥ ����
float FocusZ = 0; // ������ Z����ǥ ����
int num = 0; // ����Ű�� ���� Ƚ���� ���� gluLookAt�Լ��� ��ǥ ����
void MyInit(void) {
    glClearColor(0.0, 0.0, 0.0, 1.0); // ������ ������
    glShadeModel(GL_FLAT);
}

void MyDisplay(void) {
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW); // �𵨺� ����� glLoadIdentity()�� �ʱ�ȭ ���� ������, 
    glLoadIdentity(); // gluLookAt���� ������ ���̹Ƿ� �ݵ�� �׵���ķ� �ʱ�ȭ �ؾ���.

    // ������� �������
    // Ű�� �����Կ����� ī�޶���ġ, ������ ������
    gluLookAt(X, Y, Z, FocusX, FocusY, -50.0 + FocusZ, 0.0, 1.0, 0.0); // ������ȯ�Լ�(ī�޶���ġ, ����, ī�޶� �����)

    glPushMatrix(); // �ʱ� ���� ����

    glTranslatef(-3.0, 0.0, 0.0); // x������ -3��ŭ ���� �׸���(�հ��� ����, ���ú��� ���)
    glTranslatef(1.0, 0.0, 0.0); // ��ġ�̵�
    glPushMatrix();	// ���� ��ǥ ����
    glColor3f(1.0, 1.0, 1.0);
    glScalef(2.0, 0.4, 1.0);
    glutWireCube(1.0);
    glPopMatrix();// Ȯ������ �����

    // ������ �׸� ������ǥ���ٰ� �Ȳ�ġ �׸���
    glTranslatef(1.0, 0.0, 0.0);
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
    glTranslatef(0.3, 0.0, 0.0);
    glPushMatrix();// 1-1 �հ��� �������
    glScalef(1.2, 0.3, 0.3);
    glutWireCube(0.6);
    glPopMatrix(); // Ȯ������ �����

    // 1-2 �հ���(������ �׸� 1-1 ��Ŀ��ٰ� �׸���)
    glTranslatef(0.4, 0.0, 0.0);
    glTranslatef(0.4, 0.0, 0.0);
    glPushMatrix(); // 1-2 �հ��� ��� ����
    glScalef(1.2, 0.3, 0.3);
    glutWireCube(0.6);
    glPopMatrix(); // Ȯ������ �����

    // 1-3 �հ���
    glTranslatef(0.4, 0.0, 0.0);
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
    glTranslatef(0.4, 0.0, 0.0);
    glPushMatrix();// 2-1 �������
    glScalef(1.2, 0.3, 0.3);
    glutWireCube(0.6);
    glPopMatrix(); // Ȯ������ �����

    // 2-2 �հ���
    glTranslatef(0.4, 0.0, 0.0);
    glTranslatef(0.4, 0.0, 0.0);
    glPushMatrix(); // 2-2 �������
    glScalef(1.2, 0.3, 0.3);
    glutWireCube(0.6);
    glPopMatrix(); // Ȯ������ �����

    // 2-3 �հ���
    glTranslatef(0.4, 0.0, 0.0);
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
    glTranslatef(0.4, 0.0, 0.0);
    glPushMatrix();// 3-1 �������
    glScalef(1.2, 0.3, 0.3);
    glutWireCube(0.6);
    glPopMatrix(); // Ȯ������ �����

    // 3-2 �հ���
    glTranslatef(0.4, 0.0, 0.0);
    glTranslatef(0.4, 0.0, 0.0);
    glPushMatrix(); // 3-2 �������
    glScalef(1.2, 0.3, 0.3);
    glutWireCube(0.6);
    glPopMatrix(); // Ȯ������ �����

    // 3-3
    glTranslatef(0.4, 0.0, 0.0);
    glTranslatef(0.4, 0.0, 0.0);
    glPushMatrix(); // 3-3 �������
    glScalef(1.2, 0.3, 0.3);
    glutWireCube(0.6);
    glPopMatrix(); // Ȯ������ �����

    glPopMatrix(); // 3�� �հ��� ��

    glPopMatrix(); // �ʱ�������� ���ư���

    glutSwapBuffers();
}

void MyReshape(int w, int h) { // ������ ũ�Ⱑ ������ ��, �ְ��� �Ͼ�� �ʵ��� ������ ũ�⵵ �������ִ� �Լ�
    glViewport(0, 0, (GLsizei)w, (GLsizei)h); // ������ ������ ��ü�� �������� ����
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(65.0, (GLfloat)w / (GLfloat)h, 1.0, 20.0);
    glTranslatef(0.0, 0.0, -5.0);
}
// ��� ���⿡�� �κ����� �� �� �ֵ��� ī�޶���ġ, ������ ��ǥ�� ���⸶�� ������ �����Ͽ���
void MySpecial(int key, int x, int y) {

    switch (key) {
    // �������� ī�޶��� X,Z��ǥ, ������ X,Z��ǥ�θ� ����
    case GLUT_KEY_RIGHT: // ������Ű������ �翷������ ������
        if (num >= 26 && num <= 60) // ���� ȸ��(���ʹ������� ������)
        {
            X = X - 0.06;
            FocusX = FocusX + 2.0;
            FocusZ = FocusZ + 2.0;
        }
        else if (num >= 60 && num <= 74) // �ϼ�(���� �޺κ�)
        {
            X = X - 0.05;
            FocusX = FocusX + 2.0;
            FocusZ = FocusZ - 0.05;
        }
        else if (num >= 75 && num <= 95) // �ϼ�(���� �޺κ�)
        {
            X = X - 0.05;
            FocusX = FocusX + 2.0;
            FocusZ = FocusZ + 0.05;
            Z = Z + 0.02;
        }
        else if (num >= 96 && num<=110) // (�հ����� �ݴ� �����κ�)�Ϻ��� ������ ���� ȸ��
        {
            X = X - 0.04;
            FocusX = FocusX + 2.5;
            FocusZ = FocusZ + 0.5;
            Z = Z + 0.01;
        }
        else if (num >= 110) // (�������� ��������)������ ȸ��
        {
            X = X + 0.05;
            FocusX = FocusX + 2.5;
            FocusZ = FocusZ - 3.5;
            Z = Z + 0.005;
        }
        else // ���� ó��_ (num=0�϶�)����(�հ���)���� ȸ��
        {
            X = X + 0.06;
            FocusX = FocusX - 2.0;
            FocusZ = FocusZ + 3.0;
        }

        if (num >= 166) //160�� ȸ�� ��, ��� ��ǥ���� ���ڸ��� ��������
        {
            X = 0;
            Y = 0;
            Z = 0;
            FocusX = 0;
            FocusY = 0;
            FocusZ = 0;
            num = 0;
        }
        num++; // ����Ű ���� Ƚ�� ���
        break;
    case GLUT_KEY_UP: // ������ ����
        Y = Y + 0.01;
        FocusY = FocusY - 3.0;
        break;
    case GLUT_KEY_DOWN: // �Ʒ����� ����
        Y = Y - 0.01;
        FocusY = FocusY + 3.0;
        break;
    default:
        break;
    }

    glutPostRedisplay(); // ���÷����ݹ��Լ� ������ ȣ��
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Comprehensive Transformation");
    MyInit();
    glutDisplayFunc(MyDisplay); // �ݹ��Լ� ���
    glutReshapeFunc(MyReshape);
    glutSpecialFunc(MySpecial);
    glutMainLoop();
    return 0;
}