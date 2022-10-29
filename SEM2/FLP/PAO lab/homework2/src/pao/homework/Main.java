package pao.homework;

import java.util.concurrent.TimeUnit;

public class Main {

    public static void main(String[] args) throws InterruptedException {
        DeliveryAppHandlerFactory delivery_app_handler = new DeliveryAppHandlerFactory();

        Updates update_comanda = delivery_app_handler.createUpdate("PreluareComanda");

        update_comanda.notifyAccountAboutUpdates();

        TimeUnit.SECONDS.sleep(5);

        delivery_app_handler.createUpdate("AjungeCurand").notifyAccountAboutUpdates();

        TimeUnit.SECONDS.sleep(5);

        delivery_app_handler.createUpdate("Review").notifyAccountAboutUpdates();

    }
}
