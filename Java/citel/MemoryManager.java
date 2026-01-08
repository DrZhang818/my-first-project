import java.util.*;
import java.io.*;

public class MemoryManager {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        
        int t = sc.nextInt();
        int m = sc.nextInt();
        
        sc.nextLine(); 
        
        int idx = 0;
        int[] bel = new int[m + 1];
        
        for (int i = 0; i < t; i++) {
            String line = sc.nextLine();
            if (line.trim().isEmpty()) {
                i--; 
                continue;
            }
            
            String[] parts = line.trim().split("\\s+");
            String op = parts[0];
            
            if (op.charAt(0) == 'a') { 
                int j = 1;
                int n;

                if (parts.length == 2) {
                    n = Integer.parseInt(parts[1]);
                    int p = -1;
                    for (; j <= m - n + 1; j++) {
                        boolean ok = true;
                        for (int k = j; k < j + n; k++) {
                            if (bel[k] != 0) {
                                j = k; 
                                ok = false;
                                break;
                            }
                        }
                        if (ok) {
                            p = j;
                            break;
                        }
                    }
                    
                    if (p == -1) {
                        System.out.println("NULL");
                        continue;
                    }
                    
                    idx++;
                    Arrays.fill(bel, p, p + n, idx); 
                    System.out.println(idx);
                } else {
                    j = Integer.parseInt(parts[1]);
                    n = Integer.parseInt(parts[2]);
                    boolean ok = true;
                    if(j + n < m) {
                        for(int k = j; k < j + n; k++) {
                            if(bel[k] != 0) {
                                ok = false;
                                break;
                            }
                        }
                    } else {
                        ok = false;
                    }
                    if(!ok) {
                        System.out.println("NULL");
                    } else {
                        System.out.println(++idx);
                    }
                }
                
                
            } else if (op.charAt(0) == 'e') { 
                int x = Integer.parseInt(parts[1]);
                
                boolean found = false;
                if (x > 0) {
                    for (int k = 1; k <= m; k++) {
                        if (bel[k] == x) {
                            found = true;
                            break;
                        }
                    }
                }
                
                if (!found) {
                    System.out.println("ILLEGAL_ERASE_ARGUMENT");
                    continue;
                }
                
                for (int k = 1; k <= m; k++) {
                    if (bel[k] == x) {
                        bel[k] = 0;
                    }
                }
                
            } else { 
                int k = 0;
                int[] nbel = new int[m + 1];
                for (int j = 1; j <= m; j++) {
                    if (bel[j] != 0) {
                        nbel[++k] = bel[j];
                    }
                }
                bel = nbel;
            }
        }
    }
}