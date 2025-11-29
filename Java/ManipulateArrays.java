public class ManipulateArrays {
    public static void main(String[] args) {
        int[] array1;
        int[] array2;

        array1 = new int[] {2, 3, 5, 7, 11, 13, 17, 19};
        printArray(array1);

        array2 = array1;

        for(int i = 0; i < array1.length; i++) {
            if(i % 2 == 0) {
                array2[i] = i;
            }
        }

        printArray(array1);

        int[][] matrix = new int[5][];
        for(int i = 0; i < matrix.length; i++) {
            matrix[i] = new int[i];
            for(int j = 0; j < matrix[i].length; j++) {
                matrix[i][j] = i * j;
            }
        }

        for(int i = 0; i < matrix.length; i++) {
            System.out.printf("matrix[%d] is ", i);
            printArray(matrix[i]);
        }
    }

    public static void printArray(int[] array) {
        System.out.print('<');
        for ( int i = 0; i < array.length; i++ ) {
            System.out.print(array[i]);
            if ( (i + 1) < array.length ) {
                System.out.print(", ");
            }
        }
        System.out.println('>');
    }
}