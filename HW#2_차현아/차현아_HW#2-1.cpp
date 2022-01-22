/***********************************************************************/
/*                          HW# 2-1. GL Modeling                        */
/*  �ۼ��� : ������                              ��¥ : 2021�� 9�� 24�� */
/*                                                                      */
/* ���� ���� : 2D Primitive �����ϱ�                                    */
/*                - - - - - - -                                         */
/* ��� : 1.Points / 2.Lines / 3. LineStrip / 4. LineLoop               */
/*        5. Polygons / 6. Triangles / 7. TriangleStrip                 */
/*        8. TriangleFan / 9.Quads / 10. QuadStrip                      */
/***********************************************************************/
#include <GL/glut.h>

void MyDisplay() {
    glClear(GL_COLOR_BUFFER_BIT); // ������������
    glColor3f(1.0, 0.0, 0.0); // ���������� �׸���
    glPointSize(4.5); // ���� ũ�� ���� - ���� �� ��� �ϱ� ���� ũ�� ����
    glLineWidth(1.5); // ������ �β� ����
    glShadeModel(GL_FLAT); // �ܻ����� ĥ�ϱ� -> ����Ʈ �������� GL_SMOOTH�̹Ƿ� GL_FLAT���� �������־���.
                           // -> �÷��� ������ �������� ������ ���̱� ����
                           // GL_SMOOTH�� �Ǿ������� ������ ������ �����ϱⰡ �����

    // 1. Points - �������� �� ���
    //glBegin(GL_POINTS); // 6������ ���������� ����
    //glVertex3f(-0.5, -1.0, 0.0);
    //glVertex3f(0.5, -1.0, 0.0);
    //glVertex3f(1.0, 0.0, 0.0);
    //glVertex3f(0.5, 1.0, 0.0);
    //glVertex3f(-0.5, 1.0, 0.0);
    //glVertex3f(-1.0, 0.0, 0.0);
    //glEnd();

    // 2. Lines - �ΰ��� �������� ���� ����
    //glBegin(GL_LINES);
    //glVertex3f(-0.5, -1.0, 0.0); // ���� ���ʴ�� 2���� ¦���� �����
    //glVertex3f(0.5, -1.0, 0.0);

    //glVertex3f(1.0, 0.0, 0.0); // �ϳ��� ����
    //glVertex3f(0.5, 1.0, 0.0);

    //glVertex3f(-0.5, 1.0, 0.0); // �ϳ��� ����
    //glVertex3f(-1.0, 0.0, 0.0);
    //glEnd();

    // 3, LineStrip - ����� ����
    //glBegin(GL_LINE_STRIP);
    //glVertex3f(-0.5, -1.0, 0.0); // ���ʴ�� ����� - ó�� vertex�� ������ vertex�� �����������
    //glVertex3f(0.5, -1.0, 0.0);
    //glVertex3f(1.0, 0.0, 0.0);
    //glVertex3f(0.5, 1.0, 0.0);
    //glVertex3f(-0.5, 1.0, 0.0);
    //glVertex3f(-1.0, 0.0, 0.0);
    //glEnd();

    // 4. LineLoop - (�������� ���� ����) ����� ����
    //glBegin(GL_LINE_LOOP);
    //glVertex3f(-0.5, -1.0, 0.0); // ���ʴ�� ��������, ���������� ù���� �����
    //glVertex3f(0.5, -1.0, 0.0);  // -> 6���� ���·� �׷���
    //glVertex3f(1.0, 0.0, 0.0);
    //glVertex3f(0.5, 1.0, 0.0);
    //glVertex3f(-0.5, 1.0, 0.0);
    //glVertex3f(-1.0, 0.0, 0.0);
    //glEnd();

    // 5. Polygons - �ٰ��� 
    //glBegin(GL_POLYGON);
    //glVertex3f(-0.5, -1.0, 0.0); // ���ʴ�� �����Ͽ� �ٰ����� ����
    //glVertex3f(0.5, -1.0, 0.0);
    //glVertex3f(1.0, 0.0, 0.0);
    //glVertex3f(0.5, 1.0, 0.0);
    //glVertex3f(-0.5, 1.0, 0.0);
    //glVertex3f(-1.0, 0.0, 0.0);
    //glEnd();

    // 6. Triangles - vertex�� 3���� ������ �ﰢ��
    //glBegin(GL_TRIANGLES);
    //glVertex3f(-0.5, -1.0, 0.0); // �� �ΰ��� �ﰢ���� �������
    //glVertex3f(0.5, -1.0, 0.0);
    //glVertex3f(1.0, 0.0, 0.0);
    //glVertex3f(0.5, 1.0, 0.0);
    //glVertex3f(-0.5, 1.0, 0.0);
    //glVertex3f(-1.0, 0.0, 0.0);
    //glEnd();

    // 7. TriangleStrip - ����Ǵ� �ﰢ��
    //glBegin(GL_TRIANGLE_STRIP); // ������ ������� �����Ͽ� �̾����� �ﰢ���� �������
    //glVertex3f(1.8, -1.5, 0.0); // -> vertex 7���� 5���� �ﰢ���� �������
    //glVertex3f(1.4, 1.3, 0.0);  // ù �ﰢ���� ����� �׷���
    //glVertex3f(0.9, -0.9, 0.0);
    //// �ﰢ������ ���δٸ� ������ �����Ͽ���
    //glColor3f(0.0, 1.0, 0.0); // �׸� - �ι�° �ﰢ��
    //glVertex3f(0.0, 1.9, 0.0);
    //glColor3f(1.0, 0.0, 1.0); // ��ũ - ����° �ﰢ��
    //glVertex3f(-0.6, -1.2, 0.0);
    //glColor3f(0.0, 0.0, 1.0); // ��� - �׹�° �ﰢ��
    //glVertex3f(-1.2, 1.5, 0.0);
    //glColor3f(0.0, 0.0, 0.0); // ������ - �ټ���° �ﰢ��
    //glVertex3f(-1.8, -1.0, 0.0);
    //glEnd();

    //8. TriangleFan - �ϳ��� �߽� vertex�� �����ϴ� �ﰢ��
    //glBegin(GL_TRIANGLE_FAN); // ���� ������ ������� �����
    //glVertex3f(-1.8,-1.8, 0.0); // ���� - ù��° �ﰢ��
    //glVertex3f(1.7,-1.5,0.0);
    //glVertex3f(1.5, -0.5,0.0);
    //glColor3f(0.0, 0.0, 1.0); // ��� - �ι�° �ﰢ��
    //glVertex3f(1.1, 0.4,0.0);
    //glColor3f(1.0, 1.0, 0.0); // ��� - ����° �ﰢ��
    //glVertex3f(0.8, 1.0,0.0);
    //glColor3f(0.0, 0.0, 0.0); // �� - ������ �ﰢ��
    //glVertex3f(0.5, 1.5,0.0);
    //glEnd();

    //9. Quads - vertex�� 4���� �����Ͽ� �簢�� �׸��� 
    //glBegin(GL_QUADS); // ���ú��ǿ� ��������, ���ϻ簢���� �׷������� ������ vertex��ġ �����Ͽ���
    //glVertex3f(1.5, -1.2, 0.0); // ���� - ù��° �簢�� 
    //glVertex3f(1.5,0.6,0.0);
    //glVertex3f(0.5, 0.9,0.0);
    //glVertex3f(0.7, -1.6, 0.0);
    //glColor3f(0.0, 0.0, 0.0); // �� - �ι�° �簢��
    //glVertex3f(-0.6, -0.4, 0.0);
    //glVertex3f(-1.0, 0.5, 0.0);
    //glVertex3f(-1.8, 0.6, 0.0);
    //glVertex3f(-0.9, -1.1, 0.0);
    //glEnd();

    // 10. QuadStrip - ����Ǵ� �簢�� * vertex �� ������� ���·� ������ ������ ���°� �ƴ� ����� �� ���ϻ簢���� �������.
    glBegin(GL_QUAD_STRIP); // -> vertex�� ���ʴ�� �������� ��, �簢���� ���г��� �̾������� ����Ǹ� �ȵ� -> ���ʴ�� ���������� �簢���� ��������� �ȵ�
    glVertex3f(1.5, -1.2, 0.0); // ���� -> ù��° �簢��
    glVertex3f(1.5,0.6,0.0);
    glVertex3f(0.7, -1.6, 0.0); 
    glVertex3f(0.5, 0.9,0.0);
    glColor3f(0.0, 0.0, 0.0); // �� -> �߰� �簢��
    glVertex3f(-0.6, -0.4, 0.0);
    glVertex3f(-1.0, 0.5, 0.0);
    glVertex3f(-0.9, -1.1, 0.0); 
    glColor3f(0.0, 0.0, 1.0); // ��� -> ������ �簢��
    glVertex3f(-1.8, 0.6, 0.0);
    glVertex3f(-0.9, -1.1, 0.0);
    glEnd();

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA);
    glutInitWindowSize(500, 500); // ������ ������
    glutInitWindowPosition(20, 20); // ������ ��ġ
    glutCreateWindow("Graphics Primitives");
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glOrtho(-4.0, 4.0, -4.0, 4.0, -4.0, 4.0); // ���ú��Ǹ� ����Ͽ� vertex ��ġ�� �����Ͽ���
    glutDisplayFunc(MyDisplay); // �ݹ��Լ� ���

    glutMainLoop();
    return 0;
}