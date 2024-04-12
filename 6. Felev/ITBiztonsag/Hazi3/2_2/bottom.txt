import java.io.BufferedReader;
import java.io.InputStreamReader;

public class Bottom {
  public static void run() throws Exception {
    BufferedReader bufferedReader = new BufferedReader(new InputStreamReader(System.in));
    System.out.println("Password: ");
    String str = bufferedReader.readLine();
    if ("WX5pum7YF6WRFkX6BfZ93uAkLjC7".equals(str)) {
      System.out.println("flag{i_could_do_it_by_hand_haha}\n");
    } else {
      System.out.println("Wrong password\n");
    } 
  }
}
