class Vehicle {
    private double load, maxLoad;
    Vehicle(double x) {
        load = 0;
        maxLoad = kiloToNewts(x);
    }
    double getLoad() {
        return newtsToKilo(load);
    }
    double getMaxLoad() {
        return newtsToKilo(maxLoad);
    }
    boolean addBox(double x) {
        if(load + kiloToNewts(x) > maxLoad) {
            return false;
        }
        load += kiloToNewts(x);
        return true;
    }
    private double newtsToKilo(double x) {
        return x / 9.8;
    }
    private double kiloToNewts(double x) {
        return x * 9.8;
    }
}