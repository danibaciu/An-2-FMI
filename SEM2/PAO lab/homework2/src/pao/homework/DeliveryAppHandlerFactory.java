package pao.homework;

public class DeliveryAppHandlerFactory {
    public Updates createUpdate(String cerere)
    {
        if (cerere == null || cerere.isEmpty())
            return null;
        switch (cerere) {
            case "PreluareComanda":
                return new DeliveryAppTakeFood();
            case "AjungeCurand":
                return new DeliveryAppArriveShortly();
            case "Review":
                return new DeliveryAppReview();
            default:
                throw new IllegalArgumentException("Cerere necunoscuta ! " + cerere);
        }
    }
}
