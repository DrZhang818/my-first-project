import java.util.*;
import java.io.*;

class InvalidInputException extends RuntimeException {
    public InvalidInputException(String message) {
        super(message);
    }
}

class AgeValidator {
    public void validate(String input) {
        if(!input.matches("\\d+")) {
            throw new InvalidInputException("Invalid");
        }
        int age = Integer.parseInt(input);
        if(age < 0 || age > 150) {
            throw new InvalidInputException("Invalid");
        }

        System.out.println("OK!");
    }
}


public class Exception {
    public static void main(String[] args) {
        AgeValidator validator = new AgeValidator();

        try {
            validator.validate("25");
        } catch(InvalidInputException e) {
            System.out.println(e.getMessage());
        }

        try {
            validator.validate("250");
        } catch(InvalidInputException e) {
            System.out.println(e.getMessage());
        }
    }
}