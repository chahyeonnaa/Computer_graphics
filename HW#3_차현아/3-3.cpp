/***********************************************************************/
/*                 HW#3-3 : Mouse Callback ����                        */
/*  �ۼ��� : ������                           ��¥ : 2021�� 10�� 1��   */
/*                                                                     */
/* ���� ���� : �˸��� ����� ����ǵ��� �ڵ� 5-3 ����                  */
/*                                                                     */
/* ��� : ���콺 ��ư�� ���� ��ü �����ϱ�                             */
/*        ���ʹ�ư Ŭ�� -> ���������� 0.1�� ���������� �̵�            */
/*        ������ ��ư Ŭ�� -> �̵����� ��ü ����                       */
/*        �簢���� �������� ��迡 �����ϸ� ����                       */
/***********************************************************************/
#include <GL/glut.h>

float Delta = 0.0; // ��ü�� �̵���Ű������ �ʿ��� ����

void MyDisplay() {
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POLYGON); // �簢�� �׸���
    glColor3f(1.0, 0.0, 0.0);

    if (0.0 + Delta >= 1) // ��ü�� ������ ������ ����� �ʰ� �ϱ� ���ؼ� �簢���� ������ �� �ϳ��� x��ǥ�� 1�� �Ѿ��
        glutIdleFunc(NULL); // ���̵� �ݹ��� ���߰� �Ͽ���

    glVertex3f(-1.0 + Delta, -0.5, 0.0); // ������ �̵��� �ϸ� �ǹǷ� x��ǥ���� ������ �����ָ��
    glVertex3f(0.0 + Delta, -0.5, 0.0); 
    glVertex3f(0.0 + Delta, 0.5, 0.0); 
    glVertex3f(-1.0 + Delta, 0.5, 0.0);
    glEnd();

    glutSwapBuffers(); // �ִϸ��̼� ȿ���� ���� ������۸� ����Ͽ����Ƿ� ���۸� ���������ִ� ������ �ʿ���
}

void MyIdle() {  // ���������� 0.0005�� �̵��ϵ��� �����Ͽ���.
                 // ������ ���ǵ� 0.1�� �ϴϱ� �ʹ� ������ �������� ���� ���ϱ� ���ؼ�
    Delta = Delta + 0.0005;

    glutPostRedisplay(); // Display �ݹ� �Լ� ������ ȣ��
}
void MyMouseClick(GLint Button, GLint State, GLint X, GLint Y)
{
    if (State == GLUT_DOWN) // ��ư�� ����
    {
        switch (Button) {
        case GLUT_LEFT_BUTTON: // ���� ��ư�� ������
            glutIdleFunc(MyIdle); // ���̵� �Լ� ȣ�� -> �ƹ��ϵ� �Ͼ�� �ʴ� ���·� �������� �����̵���
                                  // �׷��� �⺻��Ҹ� ��� ����
            break;
        case GLUT_RIGHT_BUTTON: // ������ ��ư ������
            glutIdleFunc(NULL); // ���̵� �ݹ� ����(�ٽ� ������ ������ �������� ������)
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
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE); // ������۸� ���
    glutInitWindowSize(300, 300);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Mouse Callback");
    MyInit();
    glutDisplayFunc(MyDisplay); 
    glutMouseFunc(MyMouseClick); // ���콺�ݹ� ���

    glutMainLoop();
    return 0;
}