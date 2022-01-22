/***********************************************************************/
/*                 HW#3-5 : Idle Callback ����                         */
/*  �ۼ��� : ������                           ��¥ : 2021�� 10�� 1��   */
/*                                                                     */
/* ���� ���� : �˸��� ����� ����ǵ��� �ڵ� 5-7 ����                  */
/*                                                                     */
/* ��� : ����Ű�� ������,                                             */
/*        ����Ű ������ �������� ���������� �����̰���               */
/*        ��� ��ǥ�� ������ ������ ����� ������,                   */
/*        �������� ��迡 �����ϸ� ���� ��, �ٽ� ����Ű�� �����ϸ�     */
/*        �ش� �������� �ٽ� �����̵��� �����Ͽ���                     */
/***********************************************************************/
#include <GL/glut.h>

float Delta = 0.0; // y�� �̵��� ���� ����(��, �Ʒ�)
float Seta = 0.0; // x�� �̵��� ���� ����(������, �����̵�)

// �� ��ǥ���� �̵��ϰ����ϴ� �������� 0.0005��ŭ�� �̵���Ű��, ��ü ��ü�� �̵���.
// 0.1�� �̵��� �ʹ� �����⶧���� ���Ǹ� ���� 0.0005�� ����
void MyIdle() { // ��
    Delta = Delta + 0.0005;

    glutPostRedisplay(); // Display�ݹ� �Լ��� ���������� ȣ���Ŵ
}

void MyIdle2() { // �Ʒ�
    Delta = Delta - 0.0005;

    glutPostRedisplay(); // Display�ݹ� �Լ��� ���������� ȣ���Ŵ
}

void MyIdle3() { // ��
    Seta = Seta - 0.0005;

    glutPostRedisplay(); // Display�ݹ� �Լ��� ���������� ȣ���Ŵ
}

void MyIdle4() { // ������
    Seta = Seta + 0.0005;

    glutPostRedisplay(); // Display�ݹ� �Լ��� ���������� ȣ���Ŵ
}
void MyDisplay() {

    // �簢���� �������� ��迡 �������� �� ���̵� �Լ��� ����� ������ ������ ���������
    // �簢���� �� ��ǥ���� ��ġ�� ������ �ξ� ���̵� �ݹ��� ���缭 ������� �Ͽ��� 
    if (0.5 + Delta >= 1 || 0.5 + Seta >= 1 || -0.5 + Delta <= -1 || -0.5 + Seta <= -1)
    {
        glutIdleFunc(NULL);
        // ��迡�� ���߰�, �ٽ� Ű�� ������ �簢���� �����̰� �ϱ� ���ؼ� ���̵� �ݹ��� ���� ��
        // ��ǥ���� �����Ͽ� ���� if���� �ɸ��� �ʵ��� �Ͽ���
        // ��ǥ ������ �������ų� ���� 0.0005�� ��ҽ�����
        if(0.5 + Delta>=1) // ����
            Delta = Delta - 0.0005;
        else if(-0.5 + Delta<=-1) // �Ʒ���
            Delta = Delta + 0.0005;
        else if (0.5 + Seta >= 1) // ������
            Seta = Seta - 0.0005;
        else if (-0.5 + Seta <= -1) // ����
            Seta = Seta + 0.0005;
    }


    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POLYGON); // �簢�� �׸���
    glColor3f(1.0, 0.0, 0.8); // ��ũ������ �׸���
    glVertex3f(-0.5 + Seta, -0.5 + Delta, 0.0); 
    glVertex3f(0.5 + Seta, -0.5 + Delta, 0.0); 
    glVertex3f(0.5 + Seta, 0.5 + Delta, 0.0); 
    glVertex3f(-0.5 + Seta, 0.5 + Delta, 0.0); 
    glEnd();
    glutSwapBuffers(); // �ִϸ��̼� ȿ���� ���� ���߹��۸� ����Ͽ����Ƿ� ���۱�ü���� �ʿ�
}

void MySpecial(int key, int x, int y) {

    switch (key) {
    case GLUT_KEY_UP: // ���� Ű�� ������
         glutIdleFunc(MyIdle); // ��ü�� ���οö�
         break;
    case GLUT_KEY_DOWN: // �ٿ�Ű�� ������
         glutIdleFunc(MyIdle2); // ������
         break;
    case GLUT_KEY_LEFT: // ����Ű ������
         glutIdleFunc(MyIdle3); // �����̵�
         break;
    case GLUT_KEY_RIGHT: // ������ ������
         glutIdleFunc(MyIdle4); // ������ �̵�
         break;

    default:
        break;
    }

    glutPostRedisplay();
}

void MyInit() {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glOrtho(-1.0, 1.0, -1.0, 1.0, 1.0, -1.0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE); // �ִϸ��̼� ȿ���� ���� ������� ���
    glutInitWindowSize(300, 300);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Idle Callback");
    MyInit();
    glutDisplayFunc(MyDisplay);
    glutSpecialFunc(MySpecial); // ����� Ű���� �ݹ� ���(���� �ƴ� �͵��� ������)

    glutMainLoop();
    return 0;
}