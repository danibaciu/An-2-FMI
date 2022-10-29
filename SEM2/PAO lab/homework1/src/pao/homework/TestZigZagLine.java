package pao.homework;

import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.assertEquals;

public class TestZigZagLine {

    @Test
    void testSimpleLine() {
        ZigZagLine zigZagLine = new ZigZagLine(new Point(0, 0),
                new Point(0, 1));
        assertEquals(1, zigZagLine.getLength());
    }

    @Test
    void testAddExtraPoint() {
        ZigZagLine zigZagLine = new ZigZagLine(new Point(0, 0),
                new Point(0, 1));
        assertEquals(1, zigZagLine.getLength());

        zigZagLine.addPoint(new Point(1, 1));
        assertEquals(2, zigZagLine.getLength());
    }

    @Test
    void testMultipleLines() {
        ZigZagLine zigZagLine = new ZigZagLine(
                new Point(0, 0),
                new Point(0, 1),
                new Point(3, 5)
        );

        assertEquals(6, zigZagLine.getLength());
    }

    @Test
    void testLineImmutability() {
        Point p1 = new Point(0, 0);
        Point p2 = new Point(0, 1);
        ZigZagLine zigZagLine = new ZigZagLine(p1, p2);

        assertEquals(1, zigZagLine.getLength());

        p1.setX(1);

        assertEquals(1, zigZagLine.getLength());
    }
}
