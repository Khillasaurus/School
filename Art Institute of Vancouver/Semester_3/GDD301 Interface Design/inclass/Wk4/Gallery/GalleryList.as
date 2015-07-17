package 
{
	import flash.display.Sprite;
	import flash.events.Event;
	import flash.net.URLLoader;
	import flash.net.URLRequest;
	
	public class GalleryList extends Sprite
	{
		public var xmlLoader:URLLoader = new URLLoader();
		
		public var galXML:XML;

		public function GalleryList()
		{
			// constructor code
			xmlLoader.addEventListener(Event.COMPLETE, showXML);
			xmlLoader.load(new URLRequest("ImageList.xml"));
		}
		
		public function showXML(e:Event):void
		{
			galXML = new XML( e.target.data );
			var pldr:Preloader = new Preloader( galXML.theImage[0].fileLoc.text() );
			addChild( pldr );
		}

	}
	
}
