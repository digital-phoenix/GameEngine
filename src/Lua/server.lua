--server.lua
package.path = package.path .. ";Lua/?.lua"

require("utils")
local copas = require("Socket/copas");
local JSON = require("JSON")

function echoHandler(skt)
	-- print("echoHandler skt = " .. skt)
	cskt = copas.wrap(skt)
	local data_tbl = {}

	while true do
		local data = copas.receive(skt, "*l")

		if data == "" then
			break
		elseif data then
			 table.insert(data_tbl, data)
		end

		-- copas.send(skt, data)
		-- copas.sleep(0);
  	end

  	local url, verb, parts = process_data(data_tbl)
  	
  	local contentLength = tonumber(parts["content-length"])
  	print("contentLength = " .. (parts["content-length"] or ""))
  	if contentLength and contentLength > 0 then
  		local content = copas.receive(skt, contentLength)
  		
  		if parts["content-type"] == "application/json" then
  			content = JSON:decode(content)
	  		print("content = " .. (ser(content) or ""))
  		end
  	end
end

function process_data( data_tbl )
	local url, verb = process_verbs(data_tbl[1])
	
	table.remove(data_tbl, 1)
	parts = process_parts(data_tbl)

	return url, verb, parts
end

function process_verbs(verbs_line)
	local parts = split(verbs_line, " ")
	local verb = parts[1]
	local url = parts[2]
	local protocol = parts[3]

	print("process_verbs parts = " .. ser(parts) .. " verb =" .. verb .. " url=" .. url)
	return url, verb, protocol
end

function process_parts( data )
	local res = {}
	for key, word in ipairs(data) do
		local parts = split(word, ": ")
		res[parts[1]] = parts[2]
		res[string.lower(parts[1])] = parts[2]
	end

	print("process_part res = " .. ser(res))
	return res
end

server = socket.bind("*", "8086")
-- print("server  = " .. server)
copas.addserver(server, echoHandler)
copas.loop()
