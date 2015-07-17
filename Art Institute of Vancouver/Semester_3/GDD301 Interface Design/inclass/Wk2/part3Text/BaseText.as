package
{
	import flash.text.*;
	
	public class BaseText extends TextField
	{
		public var myFont = new TextFormat();
		
		public function BaseText()
		{
			myFont.font = "Arial";
			myFont.size = 72;
			myFont.color = 0xFF00FF;
			
			this.x = 10;
			this.y = 100;
			this.defaultTextFormat = myFont;
			this.type = TextFieldType.DYNAMIC;
			this.autoSize = TextFieldAutoSize.LEFT;
			this.text = String("Hello World!");
		}
	}
}