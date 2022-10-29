package pao.homework2;

public class Context {
    private Operation op;

    public Context(Operation strategy){
        this.op = strategy;
    }

    public String executeStrategy(String a, String b){
        return op.doOperation(a, b);
    }
}
