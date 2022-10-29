package pao.homework2;

public class Main {

    public static void main(String[] args) {
        Context context = new Context(new Cats());
        System.out.println(context.executeStrategy("british", "alerge"));

        context = new Context(new Dogs());
        System.out.println(context.executeStrategy("mare", "manance"));
    }
}
