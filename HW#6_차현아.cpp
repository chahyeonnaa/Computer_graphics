/***********************************************************************/
/*                 HW#6-1 : ���� ��ȯ ����                             */
/*  �ۼ��� : ������                           ��¥ : 2021�� 11�� 5��   */
/*                                                                     */
/* ���� ���� : �ڵ� 7-2 �����Ͽ� �Ʒ� ��ɿ� �°� ����                 */
/*                                                                     */
/* ��� : �ϳ��� �����츦 4���� �������� ����(���� �ϳ��� ��ü 2��)    */
/*        ���� ����: �������� / ���ϴ� ����: ��������                */
/*        Ű���� �ݹ��� �̿��Ͽ� ������ȯ�� �����                     */
/*        2- ����, 3- ���ϴ�                                         */
/* ������ȯ�� �ϰ� ���� ���� ��ȣ�� ���� �����Ͽ� Ű����� �Է��� ��, ������ ���� ����Ű�� ����� */
/* ex) ���ϴ� ������ ������ȯ �ϰ������, 3�� �Է��ѵ� ����Ű�� ����   */
/*  2,3 �����ư��鼭 �����ص� �� ������ �����Ӱ� ������ȯ ����         */
/*    ������ ũ�� ���� �� ũ�⿡ ������� ��ü�� ���°� �ְ���� ����  */
/***********************************************************************/
#include <GL/glut.h>
int kase = 0; // �������� ����
int Width, Height; // ������ ũ��
float x2 = 0, y2 = 0;
float x3 = 0, y3 = 0;

void MyInit() {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void DrawScene() { // �ٴ��̶� �����ڱ׸���
    glColor3f(0.7, 0.7, 0.7);
    glPushMatrix();
    glTranslatef(0.0, -1.0, 0.0);
    glBegin(GL_QUADS);
    glVertex3f(2.0, 0.0, 2.0);
    glVertex3f(2.0, 0.0, -2.0);
    glVertex3f(-2.0, 0.0, -2.0);
    glVertex3f(-2.0, 0.0, 2.0);
    glEnd();
    glPopMatrix();

    glColor3f(1.0, 0.2, 0.5);
    glPushMatrix();
    glTranslatef(0.0, 0.0, -0.5);
    glutWireTeapot(1.0);
    glPopMatrix();
}

void MyDisplay() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);

    //���ϴ�
    glViewport(0, 0, Width / 2, Height / 2); // ����������_�������� ���ϴܺκ�
    // ���ϴ� �������� �׸��� �׸���
    glMatrixMode(GL_PROJECTION); // ������Ľ���
    glLoadIdentity(); // �׵���ķ� �ʱ�ȭ
    glOrtho(-2.0, 2.0, -2.0, 2.0, 0.5, 5.0); // ��������
    glPushMatrix(); // ���������� �� ��Ľ��ÿ� ����

    glMatrixMode(GL_MODELVIEW); // �𵨺� ��Ľ���
    glLoadIdentity(); // �׵���ķ� �ʱ�ȭ
    glPushMatrix();
    gluLookAt(0.0 + x3, 1.0 + y3, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0); // ������ȯ
    // kase ���� 3�̸�, x3 y3������ ����Ű ���ۿ� ���� ������
    DrawScene();

    // �䷯�� �׸���
    glColor3f(0.0, 1.0, 1.0);
    glPushMatrix();
    glTranslatef(0.5, 0.5, 0.0);
    glutWireTorus(0.3, 0.5, 20, 20);
    glPopMatrix();
    glPopMatrix();

    // ����
    glViewport(Width / 2, Height / 2, Width / 2, Height / 2); // ����������_�������� ���ܺκ�
    // ���ܿ������� �׸��� �׸���.
    glMatrixMode(GL_PROJECTION); // ������Ľ���
    glLoadIdentity(); // �׵���ķ� �ʱ�ȭ
    glPushMatrix(); // ����

    gluPerspective(130, 1.0, 2.0, 0.0); // ��������_ ��ü�� �� ���ϼ��ֵ��� ���ڰ� ����
    // �ָ��ִ°� �ָ�, �������ִ� ���� �����̺���

    glMatrixMode(GL_MODELVIEW); // �𵨺� ��Ľ���
    glLoadIdentity();
    glPushMatrix();
    gluLookAt(0.0 + x2, 0.0 + y2, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0); // ������ȯ
    // kase ���� 2�̸�, x2 y2������ ����Ű ���ۿ� ���� ������
    DrawScene();

    // �䷯�� �׸���
    glColor3f(0.0, 1.0, 1.0);
    glPushMatrix();
    glTranslatef(0.5, 0.5, 0.0);
    glutWireTorus(0.3, 0.5, 20, 20);
    glPopMatrix();
    glPopMatrix();

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glFlush();
}
void MyReshape(int NewWidth, int NewHeight) // ������ ũ�� ���� �� �ְ��� �����ִ� �Լ�
{
    glViewport(0, 0, NewWidth, NewHeight); // �����Ǵ� ������ ��ü�� �������� ����
    GLfloat Widthfactor = (GLfloat)NewWidth / (GLfloat)500;
    GLfloat Heightfactor = (GLfloat)NewHeight / (GLfloat)500;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-2.0 * Widthfactor, 2.0 * Widthfactor, -2.0 * Heightfactor, 2.0 * Heightfactor, 0.5, 5.0);

}
void MyKeyboard(unsigned char key, int x, int y) { // ������ȯ�� �� ��������
    switch (key) {
    case '3': // ���ϴ� ����
        kase = 3;
        break;
    case '2': // ���� ����
        kase = 2;
        break;
    }
    glutPostRedisplay();
}
void MySpecial(int key, int x, int y) { // ������, ���� ����Ű�� ���� ����
    switch (key) {
    case GLUT_KEY_RIGHT: // kase���� ���� ������ȯ ������ �����ȴ�
        if (kase == 3)
        {
            x3 = x3 + 0.1;
            y3 = y3 + 0.1;
        }
        else if (kase == 2)
        {
            x2 = x2 + 0.1;
            y2 = y2 + 0.1;
        }
        break;
    case GLUT_KEY_LEFT:
        if (kase == 3)
        {
            x3 = x3 - 0.1;
            y3 = y3 - 0.1;
        }

        if (kase == 2)
        {
            x2 = x2 - 0.1;
            y2 = y2 - 0.1;
        }

        break;
    default:
        break;
    }
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    Width = 500;
    Height = 500;
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    glutInitWindowSize(Width, Height);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Viewpory Partition");
    MyInit();
    glutDisplayFunc(MyDisplay); // �ݹ��Լ� ���
    glutKeyboardFunc(MyKeyboard);
    glutReshapeFunc(MyReshape);
    glutSpecialFunc(MySpecial);
    glutMainLoop();
    return 0;
}