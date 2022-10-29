package pao.homework2;

public class Cats implements Operation{
    @Override
    public String doOperation(String a, String b) {
        return "Aceasta pisica are rasa " + a + " si ii place sa " + b + ".\n";
    }

}
