/***********************************************************************/
/*                 HW#3-6 : Timer Callback ����                        */
/*  �ۼ��� : ������                           ��¥ : 2021�� 10�� 1��   */
/*                                                                     */
/* ���� ���� : �˸��� ����� ����ǵ��� �ڵ� 5-8 ����                  */
/*                                                                     */
/* ��� : ���α׷� ���� �� ������ ���������� ���������� �����̰��ϱ�   */
/*        ������ ��迡 �ε����� ���� �ٲ�鼭 �������� ������ �̵�    */
/*        ���콺 ���� ��ư Ŭ�� -> �̵����� ��ü ����                  */
/***********************************************************************/
#include <GL/glut.h>
void MyTimer1(int);
void MyTimer2(int);
// Ÿ�̸� ȣ�� ���ݰ� �̵��Ÿ��� �������� ������ �����Ͽ���
GLfloat Delta = 0.0; // ��ü �̵��� ���� ����
int Case = 0; // �� Ÿ�̸Ӹ��� ���콺 ���� ��ư ������ �˷��ִ� ����(���콺 �Լ����� �޾ƿ�)

void MyDisplay() {
    glClear(GL_COLOR_BUFFER_BIT);

    glBegin(GL_POLYGON); // �簢���׸���
    glVertex3f(-1.0 + Delta, -0.5, 0.0);
    glVertex3f(0.0 + Delta, -0.5, 0.0);
    glVertex3f(0.0 + Delta, 0.5, 0.0);
    glVertex3f(-1.0 + Delta, 0.5, 0.0);
    glEnd();
    glutSwapBuffers(); // �ִϸ��̼� ȿ���� ���� ���߹��۸� ��������Ƿ� ���۱�ü���� �ʿ�
}
void MyTimer2(int Value) { // ���� �̵� Ÿ�̸�

    glColor3f(0.0, 0.0, 1.0); // �Ķ������� �� �ٲ�
    glutPostRedisplay(); // ���������� Display �ݹ� �߻���Ű��
    Delta = Delta - 0.05; // ���� �̵�

    if (Case == 1) // ���� ��ư ������ �Լ� ����
        return;

    if (-1.0 + Delta <= -1.0) // ��ü�� ������ ���� ��迡 �����ϸ�
        glutTimerFunc(40, MyTimer1, 1); // �ٽ� ���������� �̵�, Ÿ�̸�1 ȣ��
    else
        glutTimerFunc(40, MyTimer2, 1); // glut Ÿ�̸Ӵ� �Լ��� ��ϵǸ� �� �ѹ��� �̺�Ʈ�� �߻���Ű�Ƿ�
                                        // ���������� Ÿ�̸��̺�Ʈ�� �߻������־����
}

void MyTimer1(int Value) { // ������ �̵� Ÿ�̸�

    glColor3f(1.0, 0.0, 0.6); // ��ũ������ �׸��� 
    glutPostRedisplay(); // ���������� Display �ݹ� �߻���Ű��
    Delta = Delta + 0.05; // ���������� 0.05�� �̵�

    if (Case == 1) // ���� ��ư Ŭ��
        return; // Ÿ�̸� �Լ� �����Ű��

    if (Delta >= 1.0) // ��ü�� ������ ������ ��迡 �����ϸ�
    {
        glutTimerFunc(40, MyTimer2, 1); // �ٽ� �������� �̵���, Ÿ�̸�2 ȣ��(��ü�� �� �ٲ�)
    }
    else // �׷��������� Ÿ�̸�1 ȣ��
        glutTimerFunc(40, MyTimer1, 1); // glut Ÿ�̸Ӵ� �Լ��� ��ϵǸ� �� �ѹ��� �̺�Ʈ�� �߻���Ű�Ƿ�
                                        // ���������� Ÿ�̸��̺�Ʈ�� �߻������־����
}

void MyMouseClick(GLint Button, GLint State, GLint X, GLint Y)
{
    if (State == GLUT_DOWN)
    {
        switch (Button) {
        case GLUT_LEFT_BUTTON: // ���� ��ư�� ������
            Case = 1; // Case���� 1�� ����
            break;
        case GLUT_RIGHT_BUTTON: // ������ ��ư�� ������
            Case = 2; // Case ���� 2�� ����
            break;
        }
    }
}
void MyInit() {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glOrtho(-1.0, 1.0, -1.0, 1.0, 1.0, -1.0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE); // �ִϸ��̼� ȿ���� ���� ���߹��� ���
    glutInitWindowSize(300, 300);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Timer Callback");
    MyInit();
    glutDisplayFunc(MyDisplay);
    glutTimerFunc(40, MyTimer1, 1); // Ÿ�̸� �ݹ��Լ� ��� (40msec���� ȣ��)
    glutMouseFunc(MyMouseClick); // ���콺 �ݹ� ���

    glutMainLoop();
    return 0;
}