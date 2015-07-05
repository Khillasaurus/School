package
{
	import flash.display.*;
	import flash.events.*;
	
	public class DotMain extends MovieClip
	{
		
		public function DotMain()
		{
			stage.addEventListener(MouseEvent.CLICK, spawner);
		}
		
		private function spawner(event:MouseEvent):void
		{
			newDot();
		}
		
		private function newDot():void
		{
			var theDot:SmallDot = new SmallDot();
			
			theDot.x = mouseX;
			theDot.y = mouseY;
			addChild(theDot);
		}
		
	}
}