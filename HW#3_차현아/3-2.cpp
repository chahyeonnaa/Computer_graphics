/***********************************************************************/
/*                 HW#3-2 : Keyboard Callback ����                     */
/*  �ۼ��� : ������                           ��¥ : 2021�� 10�� 1��   */
/*                                                                     */
/* ���� ���� : �˸��� ����� ����ǵ��� �ڵ� 5-3 ����                  */
/*                                                                     */
/* ��� : ����Ű�� ������,                                             */
/*        ����Ű ������ �������� 0.1�� �����̰���                    */
/*        ��� ��ǥ�� ������ ������ ����� ������,                   */
/*        PageUp ��ư�� ������, �������� 0.1�� Ȯ��                    */
/*        PageDown ��ư�� ������, �������� 0.1�� ���                  */
/*        �簢���� Ȯ��� ���������� ���̴� �������� �Ͼ�� �Ͽ���,  */
/*        Ȯ��������� �� ���̶� ������ ���� �´����� Ȯ�밡 ������� �ʵ��� �Ͽ��� */
/*        �簢���� ��ġ�� ������ �� �簢���� ������� �´�����, �ʱ��ڸ��� ���ƿ����� �����Ͽ��� */
/*        �簢���� ��Ҵ� �ð������� �ּ��϶� ���̻� ��ҵ��� �ʵ��� �Ͽ��� */
/*        ������ �ʱ� ���¿��� �ִ������� ��� -> �ִ������� Ȯ�� -> �ٽ� �ּ������� ��� ������ �ݺ��ϸ�*/
/*        �ִ������� ����Ͽ��� �� �簢���� ������� ������ �߻���                         */
/*        �⺻���� Ȯ��, ��Ҵ� ���������� �۵���                      */
/***********************************************************************/

#include <GL/glut.h>
float Delta = 0.0; // x�� �̵�(������ ����)
float Seta = 0.0; // y�� �̵�(�� �Ʒ�)
float Zoomin = 0.0; // Ȯ��
float Zoomout = 0.0; // ���

void MyDisplay() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.5, 0.5, 0.5);

    glBegin(GL_POLYGON);
    // Ȯ��, ���, ���� �������� ���ÿ� �Ͼ �� �ֵ��� �Ͽ���
    glVertex3f(-0.5 - Zoomin + Zoomout + Delta, -0.5 - Zoomin + Zoomout + Seta, 0.0); //1
    glVertex3f(0.5 + Zoomin - Zoomout + Delta, -0.5 - Zoomin + Zoomout + Seta, 0.0); //2
    glVertex3f(0.5 + Zoomin - Zoomout + Delta, 0.5 + Zoomin - Zoomout + Seta, 0.0); //3
    glVertex3f(-0.5 - Zoomin + Zoomout + Delta, 0.5 + Zoomin - Zoomout + Seta, 0.0); //4
    glEnd();
    glFlush();
}

void MySpecial(int key, int x, int y) {

    switch (key) {
    case GLUT_KEY_UP: // ������ Ű�� ������,
        if (0.5 + Zoomin - Zoomout + Seta >= 1) // ��ǥ�� ������ ���� �´�����
        {
            Seta = 0; // �� �̻� ���ư��� ���ϰ� �������� �߽����� �̵�
            break;
        }
        else
        {
            Seta = Seta + 0.1; // 0.1�� ���� �̵�
            break;
        }
    case GLUT_KEY_DOWN: // �Ʒ� ����Ű�� ������
        if (-0.5 - Zoomin + Zoomout + Seta <= -1) // ��ǥ�� ������ ���� �´�����
        {
            Seta = 0; // �� �̻� ���ư��� ���ϰ� �������� �߽����� �̵�
            break;
        }
        else
        {
            Seta = Seta - 0.1; // 0.1�� �Ʒ��� �̵�
            break;
        }
    case GLUT_KEY_LEFT: // ���� ����Ű�� ������
        if (-0.5 - Zoomin + Zoomout + Delta <= -1) // ��ǥ�� ������ ���� �´�����
        {
            Delta = 0; // �� �̻� ���ư��� ���ϰ� �������� �߽����� �̵�
            break;
        }
        else
        {
            Delta = Delta - 0.1; // 0.1�� �������� �̵�
            break;
        }
    case GLUT_KEY_RIGHT: // ���� ����Ű�� ������
        if (0.5 + Zoomin - Zoomout + Delta >= 1) // ��ǥ�� ������ ���� �´�����
        {
            Delta = 0; // �� �̻� ���ư��� ���ϰ� �������� �߽����� �̵�
            break;
        }
        else
        {
            Delta = Delta + 0.1; // 0.1�� ���������� �̵�
            break;
        }
    case GLUT_KEY_PAGE_DOWN: // ���
        // ���������� �ּ��϶� �簢���� ���� : 0.01 
        if (((0.5 + Zoomin - Zoomout + Delta) - (-0.5 - Zoomin + Zoomout + Delta)) * ((0.5 + Zoomin - Zoomout + Delta) - (-0.5 - Zoomin + Zoomout + Delta)) < 0.01)
            // �ּ� ���̿� �����ϸ� �� �̻� ��ҵ��� �ʵ��� �Ͽ���
            break;
        else
        {
            Zoomout = Zoomout + 0.05; // 0.1 �� ����ؾ��ϴϱ� �� ��ǥ���� 0.05�� ����/����
            break;
        }
    case GLUT_KEY_PAGE_UP: // Ȯ��
        if (-0.5 - Zoomin + Zoomout + Delta <= -1 || -0.5 - Zoomin + Zoomout + Seta <= -1 ||
            0.5 + Zoomin - Zoomout + Delta >= 1 || -0.5 - Zoomin + Zoomout + Seta <= -1 ||
            0.5 + Zoomin - Zoomout + Delta >= 1 || 0.5 + Zoomin - Zoomout + Seta >= 1 ||
            -0.5 - Zoomin + Zoomout + Delta <= -1 || 0.5 + Zoomin - Zoomout + Seta >= 1)
            // �簢���� ��� ��ǥ���� �ϳ��� ������ ���� �´����� Ȯ����� �ʵ��� �Ͽ���
            break;
        else
        {
            Zoomin = Zoomin + 0.05; // 0.1 �� ����ؾ��ϴϱ� �� ��ǥ���� 0.05�� ����/����
            break;
        }

    default:
        break;
    }
    glutPostRedisplay(); // ���÷��� �ݹ� �Լ� ������ ȣ��
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
    glutInitWindowSize(300, 300);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Keyboard Callback");
    MyInit();
    glutDisplayFunc(MyDisplay);
    glutSpecialFunc(MySpecial);

    glutMainLoop();
    return 0;
}