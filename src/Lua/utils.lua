--utils.lua

function split(str, pattern)
	local res = {}
	local nextStart = 1
	
	
	while true do
		local start, finish = string.find(str, pattern, nextStart)

		if start == nil then
			break
		end

		table.insert(res, string.sub(str, nextStart, start - 1))
		nextStart = finish + 1
	end

	table.insert(res, string.sub(str, nextStart))
	-- print("split results str = " .. str .. " pattern= " .. pattern .. " res=" .. ser(res) )
	return res
end

function ser(tbl)
	local res = "{"
	for key, val in pairs(tbl) do
		res = res .. key .. " ="

		if type(val) == "table" then
			res = res .. ser(val)
		else
			res = res .. val
		end

		res = res .. ","
	end

	res = res .. "}"

	return res
end