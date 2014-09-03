// This is the main class for HW5
// This program is filled with compile errors.
public class Test {

   public static void main(String[] args) {
      if (args.length != 0) {
         System.out.println("Usage: java Main");
         return;
      }

      Base b = Base( );
      Derived d = new Derived( );

      b.f1( ); 
      d.f2( ); 
    }
}

