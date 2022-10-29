package pao.homework;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class ZigZagLine extends Line {

    //TODO: add code here
    private ArrayList<Point> points;

    public ZigZagLine(List<Point> points) {
        //TODO: add code here
        this.points = new ArrayList<>();
        this.points.addAll(points);
    }

    public ZigZagLine(Point... points) {
        this.points = new ArrayList<>();
        this.points.addAll(Arrays.asList(points));
    }

    public void addPoint(Point point) {
        this.points.add(point);
    }

    @Override
    public int getLength() {
        int length = 0;
        for(int i = 1; i < this.points.size(); i++) {
            Line temporar_line = new Line(this.points.get(i - 1), this.points.get(i));
            length += temporar_line.getLength();
        }
        return length;
    }

}
