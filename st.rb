require 'sinatra'
require 'keen'

get "/senddatastatus" do
    # Initialize the Keen Client.
    keen = Keen::Client.new("keentoken", "keenappkey")
    # Build your event properties as a hash.
    housecondition = {:state => {:temperature => params[:temp].to_f, :humidity => params[:hum].to_f}}
    # Add your event to the "housecondition" collection.
    keen.publish("housecondition", housecondition)
end

get "/" do
  html :index
end

def html(view)
  File.read(File.join('./', "#{view.to_s}.html"))
end
