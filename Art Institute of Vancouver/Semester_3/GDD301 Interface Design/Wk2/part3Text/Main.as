package
{
	import flash.display.*;
	
	public class Main extends MovieClip
	{
		public var baseText:BaseText = new BaseText();
		
		public function Main()
		{
			trace("Hello World!");	//sends output to output window, useful for debugging
			addChild(baseText);
			baseText.text = String("Text Control!");
		}
	}
}