require 'sinatra'
require 'keen'

get "/Afjfm3FidQuiro9K3fm2JmU" do
    # Initialize the Keen Client.
    keen = Keen::Client.new("bbc8428903734173ada2d0fd9764f82a", "E8A0CF789706C6A1E969F613C8361683")
    # Build your event properties as a hash.
    housecondition = {:state => {:temperature => params[:temp].to_f, :humidity => params[:hum].to_f, :group => "condition"}}
    # Add your event to the "housecondition" collection.
    keen.publish("housecondition", housecondition)
end

get "/" do
  html :index
end

def html(view)
  File.read(File.join('./', "#{view.to_s}.html"))
end
