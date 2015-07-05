package
{
	import flash.display.*;
	
	public class Main extends MovieClip
	{
		public var circle:Circle;
		
		public function Main()
		{
			circle = new Circle();
			addChild( circle );
		}
	}
}