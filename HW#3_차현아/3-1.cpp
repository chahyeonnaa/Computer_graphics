/***********************************************************************/
/*                 HW#3-1 : Keyboard Callback ����(1)                  */
/*  �ۼ��� : ������                           ��¥ : 2021�� 10�� 1��   */
/*                                                                     */
/* ���� ���� :  �˸��� ����� ����ǵ��� �ڵ� 5-3 ����                 */
/*                                                                     */
/* ��� : a,f,r,v,b�� �����Ͽ� ������ ��� ����                        */
/*        a - �����̵�, f - �������̵�, r- �Ʒ��� �̵�, ����ȯ         */
/*        v - ���� �̵�, b - ����ȯ                                    */
/***********************************************************************/
#include <GL/glut.h>

float Delta = 0.0; // x���̵��� ���õ� ����(���� ������)
float Seta = 0.0; // y���̵��� ���õ� ����(�Ʒ� ��)
unsigned char pwd; // Ű���� �Է°�(key)�� �޾Ƽ� �Լ� �ۿ����� key���� ����ϱ� ���� ����

void MyDisplay() {
    glClear(GL_COLOR_BUFFER_BIT);

    if (pwd == 'B' || pwd == 'b') // �޾ƿ� key���� b�̸�(����ڰ� B�� ������)
        glColor3f(0.0, 0.0, 1.0); // �Ķ������� ĥ�ϱ�
    else if (pwd == 'R' || pwd == 'r') // �޾ƿ� key���� r�̸�(����ڰ� R�� ������)
        glColor3f(1.0, 0.0, 0.0); // ���������� ĥ�ϱ�
    else
        glColor3f(0.5, 0.5, 0.5); // �׿��̸� ���� ��ȯ���� �����Ƿ� �״�� ����

    glBegin(GL_POLYGON); // �簢���׸��� - �簢�� ��ü�� �̵��ؾ��ϹǷ� ��ü��ǥ�� �̵����Ѿ���
                         // x�� �̵��̸�, x��ǥ�鿡 Delta�� �������� y�� �̵��̸�, y��ǥ�� Seta�� ������
    glVertex3f(-0.5 + Delta, -0.5 + Seta, 0.0); // 
    glVertex3f(0.5 + Delta, -0.5 + Seta, 0.0); //
    glVertex3f(0.5 + Delta, 0.5 + Seta, 0.0); //
    glVertex3f(-0.5 + Delta, 0.5 + Seta, 0.0); //
    glEnd();
    glFlush();
}

void MyKeyboard(unsigned char key, int x, int y) {

    pwd = key; // key���� �޾Ƽ� �Լ� �ۿ����� key���� ����ϱ� ���� ����

    switch (key) {
    case 'A':
    case 'a': // a�� ������
        Delta = Delta - 0.1; // �������� �̵�
        break;
    case 'F':
    case 'f': // f�� ������
        Delta = Delta + 0.1; // ���������� �̵�
        break;
    case 'R':
    case 'r': // r�� ������
        Seta = Seta - 0.1; // �Ʒ��� �̵�
        break;
    case 'V':
    case 'v': // v�� ������
        Seta = Seta + 0.1; // �������� �̵�
        break;
    case 'B':
    case 'b':
        break;
    }
    glutPostRedisplay(); // Display�ݹ��� ���������� �߻���Ű������ �Լ�
}


void MyInit() {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB);
    glutInitWindowSize(300, 300); // �����������
    glutInitWindowPosition(30, 30); // �����찡 �ߴ� ��ġ
    glutCreateWindow("Keyboard Callback 3-1");
    MyInit();
    glutDisplayFunc(MyDisplay);
    glutKeyboardFunc(MyKeyboard);// Ű���� �ݹ� ���

    glutMainLoop();
    return 0;
}